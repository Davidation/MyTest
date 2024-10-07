# coding=utf-8

import concurrent.futures
import threading
import requests
import time

from bs4 import BeautifulSoup

URL = "https://q.10jqka.com.cn"
STOCK_URL_LHS = "https://d.10jqka.com.cn/v6/line/sb_"
STOCK_URL_RHS = "/01/all.js"

HEADER = {
  'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
  'Accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
  'Accept-Encoding': "gzip, deflate, br, zstd",
  'Cache-Control': "max-age=0",
  'sec-ch-ua': "\"Google Chrome\";v=\"129\", \"Not=A?Brand\";v=\"8\", \"Chromium\";v=\"129\"",
  'sec-ch-ua-mobile': "?0",
  'sec-ch-ua-platform': "\"Windows\"",
  'Upgrade-Insecure-Requests': "1",
  'Sec-Fetch-Site': "same-site",
  'Sec-Fetch-Mode': "navigate",
  'Sec-Fetch-User': "?1",
  'Sec-Fetch-Dest': "document",
  'Referer': "https://www.10jqka.com.cn/",
  'Accept-Language': "zh-CN,zh;q=0.9",
}

STOCK_HEADER = {
  'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
  'Accept-Encoding': "gzip, deflate, br, zstd",
  'sec-ch-ua-platform': "\"Windows\"",
  'sec-ch-ua': "\"Google Chrome\";v=\"129\", \"Not=A?Brand\";v=\"8\", \"Chromium\";v=\"129\"",
  'sec-ch-ua-mobile': "?0",
  'Sec-Fetch-Site': "same-site",
  'Sec-Fetch-Mode': "no-cors",
  'Sec-Fetch-Dest': "script",
  'Referer': "https://stockpage.10jqka.com.cn/",
  'Accept-Language': "zh-CN,zh;q=0.9",
}

briefmap = {}

def stock_full_url(stock_code):
    return STOCK_URL_LHS + stock_code + STOCK_URL_RHS

def query_one(idx):
    fullurl = stock_full_url(briefmap[idx])
    resp = requests.get(fullurl, headers=STOCK_HEADER)
    print('idx: {} \tfullurl: {} \ttext: {}\n'.format(idx, fullurl, resp.text))

def query_all():
    print('brief len {}'.format(len(briefmap)))
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
        todo = []
        for idx, code in briefmap.items():
            future = executor.submit(query_one, idx)
            todo.append(future)

        for future in concurrent.futures.as_completed(todo):
            future.result()


def main():
    init_page = requests.get(URL, headers=HEADER).content
    init_soup = BeautifulSoup(init_page, 'lxml')

    total_num = 0
    nums, codes, names, stock_urls = [], [], [], []

    tbody = init_soup.find('tbody')
    for each_stocks in tbody.find_all('tr'):
        all_col = each_stocks.find_all('td')

        nums.append(all_col[0].text)
        codes.append(all_col[1].text)

        global briefmap
        briefmap[all_col[0].text] = all_col[1].text
        names.append(all_col[2].text)
        stock_urls.append(STOCK_URL_LHS + all_col[1].text + STOCK_URL_RHS)
        total_num += 1

    query_all()

if __name__ == '__main__':
    start = time.perf_counter()
    main()
    end = time.perf_counter()
    print("total cost {} seconds".format(end - start))



'''
init_soup:
                <thead>
                <tr>
                    <th style="width:4%">序号</th>
                    <th style="width:6%">代码</th>
                    <th style="width:8%">名称</th>
                    <th style="width:6%" ><a href="javascript:void(0)" field="xj" >现价<i></i></a></th>
                    <th style="width:8%"  class="cur"><a href="javascript:void(0)" field="zdf" order="desc"  class="desc">涨跌幅(%)<i></i></a></th>
                    <th style="width:6%" ><a href="javascript:void(0)" field="zd" >涨跌<i></i></a></th>
                    <th style="width:8%" ><a href="javascript:void(0)" field="zs" >涨速(%)<i></i></a></th>
                    <th style="width:8%" ><a href="javascript:void(0)" field="hs" >换手(%)<i></i></a></th>
                    <th style="width:6%" ><a href="javascript:void(0)" field="lb" >量比<i></i></a></th>
                    <th style="width:6%" ><a href="javascript:void(0)" field="zf" >振幅(%)<i></i></a></th>
                    <th style="width:7%" ><a href="javascript:void(0)" field="cje" >成交额<i></i></a></th>
                    <th style="width:8%" ><a href="javascript:void(0)" field="ltg" >流通股<i></i></a></th>
                    <th style="width:8%" ><a href="javascript:void(0)" field="ltsz" >流通市值<i></i></a></th>
                    <th style="width:7%" ><a href="javascript:void(0)" field="syl" >市盈率<i></i></a></th>
                    <!--th>概念题材</th-->
                    <th style="width:4%">加自选</th>
                </tr>
                </thead>
                <tbody>
                                <tr>
                    <td>1</td>
                    <td><a href="http://stockpage.10jqka.com.cn/301618/" target="_blank">301618</a></td>
                    <td><a href="http://stockpage.10jqka.com.cn/301618/" target="_blank">N长联</a></td>
                    <td class="c-rise">381.00</td>
                    <td class="c-rise">1703.98</td>
                    <td class="c-rise">359.88</td>
                    <td class="c-rise">0.03</td>
                    <td>91.38</td>
                    <td class="">--</td>
                    <td class="c-rise">1463.07</td>
                    <td>21.20亿</td>
                    <td>1611.00万</td>
                    <td>61.38亿</td>
                    <td>273.66</td>
                    <td><a class="j_addStock" title="加自选" href="javascript:void(0);"><img src="http://i.thsi.cn/images/q/plus_logo.png" alt=""></a></td>
                </tr>
'''



