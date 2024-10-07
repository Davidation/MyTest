#import requests
#
#url = "https://d.10jqka.com.cn/v6/line/sb_301618/01/all.js"
#
#headers = {
#  'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36",
#  'Accept-Encoding': "gzip, deflate, br, zstd",
#  'Pragma': "no-cache",
#  'Cache-Control': "no-cache",
#  'sec-ch-ua-platform': "\"Windows\"",
#  'sec-ch-ua': "\"Google Chrome\";v=\"129\", \"Not=A?Brand\";v=\"8\", \"Chromium\";v=\"129\"",
#  'sec-ch-ua-mobile': "?0",
#  'Sec-Fetch-Site': "same-site",
#  'Sec-Fetch-Mode': "no-cors",
#  'Sec-Fetch-Dest': "script",
#  'Referer': "https://stockpage.10jqka.com.cn/",
#  'Accept-Language': "zh-CN,zh;q=0.9",
#  'Cookie': "u_ukey=A10702B8689642C6BE607730E11E6E4A; u_uver=1.0.0; u_dpass=KT2fOogfQgvF5LzsUtcxHjWHP9epKMZ8aVKfbw08nsgTy4x2cVX9HPwiQrKXT%2FqtHi80LrSsTFH9a%2B6rtRvqGg%3D%3D; u_did=064C588EFF5242E78BB0FCDA07E250A0; u_ttype=WEB; __utma=156575163.1100859677.1728233763.1728233763.1728233763.1; __utmz=156575163.1728233763.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); Hm_lvt_722143063e4892925903024537075d0d=1727969307,1728230140,1728233743,1728275307; Hm_lpvt_722143063e4892925903024537075d0d=1728275307; HMACCOUNT=D76A6477C3BE16A2; log=; Hm_lvt_929f8b362150b1f77b477230541dbbc2=1727969307,1728230140,1728233743,1728275307; Hm_lpvt_929f8b362150b1f77b477230541dbbc2=1728275307; Hm_lvt_78c58f01938e4d85eaf619eae71b4ed1=1727969307,1728230140,1728233743,1728275307; spversion=20130314; historystock=832876%7C*%7C301551; Hm_lpvt_78c58f01938e4d85eaf619eae71b4ed1=1728276283; v=A8Pl97KFoCnkNmxdgkzLjCApUoxoOFZikcybrPWgHyKZtO1yfQjnyqGcK_oG"
#}
#
#response = requests.get(url, headers=headers)
#
#print(response.text)


import requests

url = "https://d.10jqka.com.cn/v6/line/hs_301551/21/all.js"

headers = {
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
  'Cookie': "u_ukey=A10702B8689642C6BE607730E11E6E4A; u_uver=1.0.0; u_dpass=KT2fOogfQgvF5LzsUtcxHjWHP9epKMZ8aVKfbw08nsgTy4x2cVX9HPwiQrKXT%2FqtHi80LrSsTFH9a%2B6rtRvqGg%3D%3D; u_did=064C588EFF5242E78BB0FCDA07E250A0; u_ttype=WEB; __utma=156575163.1100859677.1728233763.1728233763.1728233763.1; __utmz=156575163.1728233763.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); Hm_lvt_722143063e4892925903024537075d0d=1727969307,1728230140,1728233743,1728275307; Hm_lpvt_722143063e4892925903024537075d0d=1728275307; HMACCOUNT=D76A6477C3BE16A2; log=; Hm_lvt_929f8b362150b1f77b477230541dbbc2=1727969307,1728230140,1728233743,1728275307; Hm_lpvt_929f8b362150b1f77b477230541dbbc2=1728275307; Hm_lvt_78c58f01938e4d85eaf619eae71b4ed1=1727969307,1728230140,1728233743,1728275307; spversion=20130314; historystock=301551%7C*%7C832876; Hm_lpvt_78c58f01938e4d85eaf619eae71b4ed1=1728277332; v=A4-pE2YJNIUE8jB5-rTf8FxtHiictOG7fQrni6GcK2UFeqHWqYRzJo3YdxCy"
}

response = requests.get(url, headers=headers)

print(response.text)
