# 交易执行模块

import requests
from datetime import datetime
from config import THS_API_CONFIG, TRADE_CONFIG
from logging_config import trade_logger

class TradeExecutor:
    """交易执行器，通过同花顺API执行交易操作"""
    
    def __init__(self, data_fetcher):
        self.data_fetcher = data_fetcher
        self.base_url = THS_API_CONFIG['base_url']
        self.timeout = THS_API_CONFIG['timeout']
    
    def place_order(self, stock_code, direction, price, quantity):
        """下单操作
        
        Args:
            stock_code: 股票代码
            direction: 交易方向，1为买入，-1为卖出
            price: 交易价格
            quantity: 交易数量
            
        Returns:
            dict: 下单结果
        """
        try:
            token = self.data_fetcher._get_token()
            if not token:
                trade_logger.error("获取访问令牌失败，无法下单")
                return {'success': False, 'msg': '获取访问令牌失败'}
            
            url = f"{self.base_url}/trade/order"
            params = {
                'token': token,
                'code': stock_code,
                'direction': 'buy' if direction == 1 else 'sell',
                'price': price,
                'quantity': quantity,
                'order_type': 'limit'  # 限价单
            }
            response = requests.post(url, json=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                order_id = result['data']['order_id']
                trade_logger.info(f"下单成功，股票: {stock_code}，方向: {'买入' if direction == 1 else '卖出'}，价格: {price}，数量: {quantity}，订单ID: {order_id}")
                return {'success': True, 'order_id': order_id, 'msg': '下单成功'}
            else:
                trade_logger.error(f"下单失败: {result['msg']}")
                return {'success': False, 'msg': result['msg']}
        except Exception as e:
            trade_logger.error(f"下单异常: {str(e)}")
            return {'success': False, 'msg': str(e)}
    
    def cancel_order(self, order_id):
        """撤单操作
        
        Args:
            order_id: 订单ID
            
        Returns:
            dict: 撤单结果
        """
        try:
            token = self.data_fetcher._get_token()
            if not token:
                trade_logger.error("获取访问令牌失败，无法撤单")
                return {'success': False, 'msg': '获取访问令牌失败'}
            
            url = f"{self.base_url}/trade/cancel"
            params = {
                'token': token,
                'order_id': order_id
            }
            response = requests.post(url, json=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                trade_logger.info(f"撤单成功，订单ID: {order_id}")
                return {'success': True, 'msg': '撤单成功'}
            else:
                trade_logger.error(f"撤单失败: {result['msg']}")
                return {'success': False, 'msg': result['msg']}
        except Exception as e:
            trade_logger.error(f"撤单异常: {str(e)}")
            return {'success': False, 'msg': str(e)}
    
    def get_order_status(self, order_id):
        """获取订单状态
        
        Args:
            order_id: 订单ID
            
        Returns:
            dict: 订单状态
        """
        try:
            token = self.data_fetcher._get_token()
            if not token:
                trade_logger.error("获取访问令牌失败，无法查询订单状态")
                return {'success': False, 'msg': '获取访问令牌失败'}
            
            url = f"{self.base_url}/trade/order_status"
            params = {
                'token': token,
                'order_id': order_id
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                order_status = result['data']
                trade_logger.info(f"查询订单状态成功，订单ID: {order_id}，状态: {order_status['status']}")
                return {'success': True, 'data': order_status}
            else:
                trade_logger.error(f"查询订单状态失败: {result['msg']}")
                return {'success': False, 'msg': result['msg']}
        except Exception as e:
            trade_logger.error(f"查询订单状态异常: {str(e)}")
            return {'success': False, 'msg': str(e)}
    
    def execute_trades(self, signals):
        """执行交易信号
        
        Args:
            signals: 交易信号，格式为 {stock_code: {'signal': 1/-1, 'price': float, 'quantity': int}}
            
        Returns:
            dict: 执行结果
        """
        try:
            results = {}
            
            # 检查是否在交易时间内
            if not self._is_trading_hours():
                trade_logger.warning("当前不在交易时间内，无法执行交易")
                return {'success': False, 'msg': '当前不在交易时间内'}
            
            # 执行交易
            for stock_code, signal_info in signals.items():
                direction = signal_info['signal']
                price = signal_info['price']
                quantity = signal_info['quantity']
                
                # 下单
                result = self.place_order(stock_code, direction, price, quantity)
                results[stock_code] = result
            
            trade_logger.info(f"执行交易完成，处理信号数量: {len(signals)}")
            return {'success': True, 'results': results}
        except Exception as e:
            trade_logger.error(f"执行交易异常: {str(e)}")
            return {'success': False, 'msg': str(e)}
    
    def _is_trading_hours(self):
        """检查是否在交易时间内
        
        Returns:
            bool: 是否在交易时间内
        """
        try:
            now = datetime.now()
            current_time = now.strftime('%H:%M')
            current_date = now.strftime('%Y-%m-%d')
            
            # 检查是否为交易日
            # 这里简化处理，实际应该调用API查询
            weekday = now.weekday()
            if weekday >= 5:  # 周六周日
                return False
            
            # 检查是否在交易时间内
            trade_hours = TRADE_CONFIG['trade_hours']
            morning_start = trade_hours['morning_start']
            morning_end = trade_hours['morning_end']
            afternoon_start = trade_hours['afternoon_start']
            afternoon_end = trade_hours['afternoon_end']
            
            # 上午交易时间
            if morning_start <= current_time <= morning_end:
                return True
            # 下午交易时间
            if afternoon_start <= current_time <= afternoon_end:
                return True
            
            return False
        except Exception as e:
            trade_logger.error(f"检查交易时间异常: {str(e)}")
            return False
    
    def get_trade_history(self, start_date, end_date):
        """获取交易历史
        
        Args:
            start_date: 开始日期，格式为 '2024-01-01'
            end_date: 结束日期，格式为 '2024-01-31'
            
        Returns:
            list: 交易历史记录
        """
        try:
            token = self.data_fetcher._get_token()
            if not token:
                trade_logger.error("获取访问令牌失败，无法查询交易历史")
                return []
            
            url = f"{self.base_url}/trade/history"
            params = {
                'token': token,
                'start_date': start_date,
                'end_date': end_date
            }
            response = requests.get(url, params=params, timeout=self.timeout)
            result = response.json()
            
            if result['code'] == 0:
                history = result['data']
                trade_logger.info(f"获取交易历史成功，记录条数: {len(history)}")
                return history
            else:
                trade_logger.error(f"获取交易历史失败: {result['msg']}")
                return []
        except Exception as e:
            trade_logger.error(f"获取交易历史异常: {str(e)}")
            return []
