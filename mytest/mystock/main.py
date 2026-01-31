# 主程序文件

import time
from datetime import datetime, timedelta
import pandas as pd
from data_fetcher import DataFetcher
from technical_indicators import TechnicalIndicators
from strategy import Strategy
from trade_executor import TradeExecutor
from position_manager import PositionManager
from config import STOCK_POOL, TRADE_CONFIG
from logging_config import system_logger, strategy_logger, trade_logger

class QuantTradingSystem:
    """量化交易系统"""
    
    def __init__(self):
        self.data_fetcher = DataFetcher()
        self.position_manager = PositionManager(self.data_fetcher)
        self.technical_indicators = TechnicalIndicators()
        self.strategy = Strategy()
        self.trade_executor = TradeExecutor(self.data_fetcher)
        self.stock_pool = STOCK_POOL
        self.last_trade_time = None
    
    def run(self):
        """运行量化交易系统"""
        try:
            system_logger.info("量化交易系统启动")
            
            while True:
                # 检查是否在交易时间内
                if self._is_trading_hours():
                    # 检查是否需要执行交易（避免过于频繁）
                    if self._should_trade():
                        system_logger.info("开始执行交易周期")
                        self._execute_trade_cycle()
                        self.last_trade_time = datetime.now()
                    else:
                        system_logger.debug("交易频率限制，跳过本次执行")
                else:
                    system_logger.debug("当前不在交易时间内，等待...")
                
                # 休眠一段时间
                time.sleep(60)  # 每分钟检查一次
                
        except KeyboardInterrupt:
            system_logger.info("量化交易系统手动停止")
        except Exception as e:
            system_logger.error(f"量化交易系统异常: {str(e)}")
    
    def _execute_trade_cycle(self):
        """执行一个交易周期"""
        try:
            # 1. 获取实时行情数据
            system_logger.info("获取实时行情数据")
            realtime_data = self.data_fetcher.get_realtime_data(self.stock_pool)
            
            if realtime_data is None:
                system_logger.error("获取实时行情数据失败，跳过本次交易周期")
                return
            
            # 2. 获取历史行情数据
            system_logger.info("获取历史行情数据")
            end_date = datetime.now().strftime('%Y-%m-%d')
            start_date = (datetime.now() - timedelta(days=60)).strftime('%Y-%m-%d')
            
            historical_data = {}
            for stock_code in self.stock_pool:
                stock_data = self.data_fetcher.get_historical_data(stock_code, start_date, end_date)
                if stock_data is not None:
                    historical_data[stock_code] = stock_data
            
            if not historical_data:
                system_logger.error("获取历史行情数据失败，跳过本次交易周期")
                return
            
            # 3. 计算技术指标
            system_logger.info("计算技术指标")
            indicator_data = {}
            for stock_code, data in historical_data.items():
                indicator_data[stock_code] = self.technical_indicators.calculate_all_indicators(data)
            
            # 4. 获取持仓信息和摘要
            system_logger.info("获取持仓信息")
            position = self.position_manager.get_position()
            position_summary = self.position_manager.get_position_summary()
            system_logger.info(f"持仓摘要: {position_summary}")
            
            # 5. 检查止损止盈
            system_logger.info("检查止损止盈")
            sl_tp_signals = self.position_manager.check_stop_loss_take_profit(realtime_data)
            
            # 6. 生成交易信号
            system_logger.info("生成交易信号")
            # 合并数据
            combined_data = self._combine_data(indicator_data)
            strategy_signals = self.strategy.generate_signals(combined_data, position)
            
            # 7. 合并信号
            signals = {**strategy_signals, **sl_tp_signals}
            
            # 8. 检查持仓限制
            filtered_signals = {}
            for stock_code, signal_info in signals.items():
                if signal_info['signal'] == 1:
                    # 买入信号，检查持仓限制
                    order_amount = signal_info.get('price', 0) * signal_info.get('quantity', 0)
                    if self.position_manager.check_position_limits(stock_code, order_amount):
                        filtered_signals[stock_code] = signal_info
                else:
                    # 卖出信号，无需检查持仓限制
                    filtered_signals[stock_code] = signal_info
            
            # 9. 执行交易
            if filtered_signals:
                system_logger.info(f"执行交易，信号数量: {len(filtered_signals)}")
                result = self.trade_executor.execute_trades(filtered_signals)
                if result['success']:
                    system_logger.info("交易执行成功")
                else:
                    system_logger.error(f"交易执行失败: {result['msg']}")
            else:
                system_logger.info("无交易信号，跳过执行")
            
        except Exception as e:
            system_logger.error(f"执行交易周期失败: {str(e)}")
    
    def _combine_data(self, indicator_data):
        """合并多只股票的指标数据
        
        Args:
            indicator_data: 字典，格式为 {stock_code: DataFrame}
            
        Returns:
            DataFrame: 合并后的数据
        """
        try:
            # 这里简化处理，实际应该根据需要合并数据
            # 这里返回最新的指标数据
            latest_data = []
            for stock_code, data in indicator_data.items():
                if not data.empty:
                    latest = data.iloc[-1].copy()
                    latest['stock_code'] = stock_code
                    latest_data.append(latest)
            
            if latest_data:
                return pd.DataFrame(latest_data).set_index('stock_code')
            else:
                return pd.DataFrame()
        except Exception as e:
            system_logger.error(f"合并数据失败: {str(e)}")
            return pd.DataFrame()
    
    def _is_trading_hours(self):
        """检查是否在交易时间内
        
        Returns:
            bool: 是否在交易时间内
        """
        return self.trade_executor._is_trading_hours()
    
    def _should_trade(self):
        """检查是否应该执行交易
        
        Returns:
            bool: 是否应该执行交易
        """
        if self.last_trade_time is None:
            return True
        
        # 检查时间间隔（至少5分钟）
        time_diff = datetime.now() - self.last_trade_time
        return time_diff.total_seconds() >= 300

if __name__ == "__main__":
    # 创建并运行系统
    system = QuantTradingSystem()
    system.run()
