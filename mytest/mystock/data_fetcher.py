# 数据获取模块

import requests
import pandas as pd
from datetime import datetime, timedelta
from config import THS_API_CONFIG
from logging_config import data_logger

class DataFetcher:
    """数据获取器，从同花顺API获取行情数据"""
    
    def __init__(self):
        self.app_key = THS_API_CONFIG['app_key']
        self.app_secret = THS_API_CONFIG['app_secret']
        self.base_url = THS_API_CONFIG['base_url']
        self.timeout = THS_API_CONFIG['timeout']
        self.token = None
        self.token_expire_time = None
    
    def _get_token(self):
        """获取访问令牌"""
        if self.token and datetime.now() < self.token_expire_time:
            return self.token
        
        try:
            url = f"{self.base_url}/auth"
            params = {
                'app_key': self.app_key,
                'app_secret': self.app_secret
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                self.token = result['data']['token']
                self.token_expire_time = datetime.now() + timedelta(hours=23)
                data_logger.info("获取访问令牌成功")
                return self.token
            else:
                data_logger.error(f"获取访问令牌失败: {result['msg']}")
                return None
        except Exception as e:
            data_logger.error(f"获取访问令牌异常: {str(e)}")
            return None
    
    def get_realtime_data(self, stock_codes):
        """获取实时行情数据
        
        Args:
            stock_codes: 股票代码列表，如 ['600519.SH', '000858.SZ']
            
        Returns:
            DataFrame: 实时行情数据
        """
        try:
            token = self._get_token()
            if not token:
                return None
            
            url = f"{self.base_url}/market/quote"
            params = {
                'token': token,
                'codes': ','.join(stock_codes)
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                data = result['data']
                df = pd.DataFrame(data)
                data_logger.info(f"获取实时行情数据成功，股票数量: {len(df)}")
                return df
            else:
                data_logger.error(f"获取实时行情数据失败: {result['msg']}")
                return None
        except Exception as e:
            data_logger.error(f"获取实时行情数据异常: {str(e)}")
            return None
    
    def get_historical_data(self, stock_code, start_date, end_date, frequency='1d'):
        """获取历史行情数据
        
        Args:
            stock_code: 股票代码，如 '600519.SH'
            start_date: 开始日期，如 '2024-01-01'
            end_date: 结束日期，如 '2024-01-31'
            frequency: 数据频率，如 '1d'(日线), '60m'(60分钟线), '5m'(5分钟线)
            
        Returns:
            DataFrame: 历史行情数据
        """
        try:
            token = self._get_token()
            if not token:
                return None
            
            url = f"{self.base_url}/market/history"
            params = {
                'token': token,
                'code': stock_code,
                'start_date': start_date,
                'end_date': end_date,
                'frequency': frequency
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                data = result['data']
                df = pd.DataFrame(data)
                # 转换日期格式
                if 'date' in df.columns:
                    df['date'] = pd.to_datetime(df['date'])
                data_logger.info(f"获取历史行情数据成功，{stock_code}，数据条数: {len(df)}")
                return df
            else:
                data_logger.error(f"获取历史行情数据失败: {result['msg']}")
                return None
        except Exception as e:
            data_logger.error(f"获取历史行情数据异常: {str(e)}")
            return None
    
    def get_account_info(self):
        """获取账户信息
        
        Returns:
            dict: 账户信息
        """
        try:
            token = self._get_token()
            if not token:
                return None
            
            url = f"{self.base_url}/account/info"
            params = {
                'token': token
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                data = result['data']
                data_logger.info("获取账户信息成功")
                return data
            else:
                data_logger.error(f"获取账户信息失败: {result['msg']}")
                return None
        except Exception as e:
            data_logger.error(f"获取账户信息异常: {str(e)}")
            return None
    
    def get_position(self):
        """获取持仓信息
        
        Returns:
            DataFrame: 持仓信息
        """
        try:
            token = self._get_token()
            if not token:
                return None
            
            url = f"{self.base_url}/account/position"
            params = {
                'token': token
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                data = result['data']
                df = pd.DataFrame(data)
                data_logger.info(f"获取持仓信息成功，持仓数量: {len(df)}")
                return df
            else:
                data_logger.error(f"获取持仓信息失败: {result['msg']}")
                return None
        except Exception as e:
            data_logger.error(f"获取持仓信息异常: {str(e)}")
            return None
