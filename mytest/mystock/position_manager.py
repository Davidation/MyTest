# 仓位管理模块

import pandas as pd
from datetime import datetime
from config import TRADE_CONFIG
from logging_config import system_logger

class PositionManager:
    """仓位管理类"""
    
    def __init__(self, data_fetcher):
        self.data_fetcher = data_fetcher
        self.max_position_per_stock = TRADE_CONFIG['max_position_per_stock']
        self.stop_loss_ratio = TRADE_CONFIG['stop_loss_ratio']
        self.take_profit_ratio = TRADE_CONFIG['take_profit_ratio']
        self.current_position = None
        self.last_update_time = None
    
    def get_position(self):
        """获取当前持仓信息
        
        Returns:
            DataFrame: 持仓信息
        """
        try:
            # 从API获取持仓信息
            position = self.data_fetcher.get_position()
            
            if position is not None:
                self.current_position = position
                self.last_update_time = datetime.now()
                system_logger.info(f"获取持仓信息成功，持仓数量: {len(position)}")
            else:
                system_logger.error("获取持仓信息失败")
            
            return self.current_position
        except Exception as e:
            system_logger.error(f"获取持仓信息异常: {str(e)}")
            return None
    
    def calculate_position_ratio(self):
        """计算持仓比例
        
        Returns:
            dict: 持仓比例，格式为 {stock_code: ratio}
        """
        try:
            if self.current_position is None:
                return {}
            
            total_market_value = self.current_position['market_value'].sum()
            if total_market_value == 0:
                return {}
            
            position_ratios = {}
            for _, row in self.current_position.iterrows():
                stock_code = row['stock_code']
                market_value = row['market_value']
                ratio = market_value / total_market_value
                position_ratios[stock_code] = ratio
            
            system_logger.info("计算持仓比例成功")
            return position_ratios
        except Exception as e:
            system_logger.error(f"计算持仓比例异常: {str(e)}")
            return {}
    
    def check_position_limits(self, stock_code, order_amount):
        """检查持仓限制
        
        Args:
            stock_code: 股票代码
            order_amount: 下单金额
            
        Returns:
            bool: 是否符合持仓限制
        """
        try:
            # 获取当前持仓
            position = self.get_position()
            if position is None:
                return True  # 无持仓信息，默认允许
            
            # 计算当前持仓比例
            position_ratios = self.calculate_position_ratio()
            current_ratio = position_ratios.get(stock_code, 0)
            
            # 计算下单后可能的持仓比例
            total_market_value = position['market_value'].sum()
            new_ratio = (current_ratio * total_market_value + order_amount) / (total_market_value + order_amount)
            
            # 检查是否超过最大持仓比例
            if new_ratio > self.max_position_per_stock:
                system_logger.warning(f"持仓比例超过限制，股票: {stock_code}，当前比例: {current_ratio:.2%}，下单后比例: {new_ratio:.2%}，最大限制: {self.max_position_per_stock:.2%}")
                return False
            
            return True
        except Exception as e:
            system_logger.error(f"检查持仓限制异常: {str(e)}")
            return False
    
    def check_stop_loss_take_profit(self, realtime_data):
        """检查止损止盈
        
        Args:
            realtime_data: 实时行情数据
            
        Returns:
            dict: 止损止盈信号，格式为 {stock_code: {'signal': -1, 'price': float, 'reason': 'stop_loss/take_profit'}}
        """
        try:
            signals = {}
            
            # 获取当前持仓
            position = self.get_position()
            if position is None:
                return signals
            
            # 遍历持仓
            for _, row in position.iterrows():
                stock_code = row['stock_code']
                cost_price = row['cost_price']
                current_price = realtime_data[realtime_data['code'] == stock_code]['price'].iloc[0] if not realtime_data[realtime_data['code'] == stock_code].empty else 0
                
                if current_price == 0:
                    continue
                
                # 计算收益率
                return_ratio = (current_price - cost_price) / cost_price
                
                # 检查止损
                if return_ratio <= -self.stop_loss_ratio:
                    signals[stock_code] = {
                        'signal': -1,
                        'price': current_price,
                        'reason': 'stop_loss'
                    }
                    system_logger.info(f"触发止损，股票: {stock_code}，成本价: {cost_price}，当前价: {current_price}，收益率: {return_ratio:.2%}")
                # 检查止盈
                elif return_ratio >= self.take_profit_ratio:
                    signals[stock_code] = {
                        'signal': -1,
                        'price': current_price,
                        'reason': 'take_profit'
                    }
                    system_logger.info(f"触发止盈，股票: {stock_code}，成本价: {cost_price}，当前价: {current_price}，收益率: {return_ratio:.2%}")
            
            return signals
        except Exception as e:
            system_logger.error(f"检查止损止盈异常: {str(e)}")
            return {}
    
    def get_position_summary(self):
        """获取持仓摘要
        
        Returns:
            dict: 持仓摘要
        """
        try:
            position = self.get_position()
            if position is None:
                return {
                    'total_stocks': 0,
                    'total_market_value': 0,
                    'total_cost': 0,
                    'total_profit': 0,
                    'profit_ratio': 0
                }
            
            total_stocks = len(position)
            total_market_value = position['market_value'].sum()
            total_cost = (position['cost_price'] * position['quantity']).sum()
            total_profit = total_market_value - total_cost
            profit_ratio = total_profit / total_cost if total_cost > 0 else 0
            
            summary = {
                'total_stocks': total_stocks,
                'total_market_value': total_market_value,
                'total_cost': total_cost,
                'total_profit': total_profit,
                'profit_ratio': profit_ratio
            }
            
            system_logger.info(f"获取持仓摘要成功，总股票数: {total_stocks}，总市值: {total_market_value:.2f}，总盈亏: {total_profit:.2f}，盈亏比例: {profit_ratio:.2%}")
            return summary
        except Exception as e:
            system_logger.error(f"获取持仓摘要异常: {str(e)}")
            return {}
