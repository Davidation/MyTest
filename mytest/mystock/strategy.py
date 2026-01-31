# 交易策略模块

import pandas as pd
from datetime import datetime
from config import STRATEGY_CONFIG, TRADE_CONFIG
from logging_config import strategy_logger

class Strategy:
    """交易策略类"""
    
    def __init__(self):
        self.strategy_name = STRATEGY_CONFIG['strategy_name']
        self.lookback_period = STRATEGY_CONFIG['lookback_period']
        self.signal_threshold = STRATEGY_CONFIG['signal_threshold']
        self.min_holding_period = STRATEGY_CONFIG['min_holding_period']
        self.max_position_per_stock = TRADE_CONFIG['max_position_per_stock']
    
    def generate_signals(self, data, position=None):
        """生成交易信号
        
        Args:
            data: DataFrame，包含技术指标数据
            position: DataFrame，当前持仓信息
            
        Returns:
            dict: 交易信号，格式为 {stock_code: {'signal': 1/-1, 'price': float, 'quantity': int}}
        """
        try:
            signals = {}
            
            # 获取最新数据
            latest_data = data.iloc[-1]
            
            # 遍历股票
            for stock_code in latest_data.index.get_level_values(0).unique() if isinstance(latest_data.index, pd.MultiIndex) else [latest_data.name]:
                # 获取股票数据
                stock_data = data[data.index.get_level_values(0) == stock_code] if isinstance(data.index, pd.MultiIndex) else data
                latest_stock_data = stock_data.iloc[-1]
                
                # 计算综合信号
                total_signal = latest_stock_data.get('total_signal', 0)
                
                # 确定交易信号
                signal = 0
                if total_signal >= 2:
                    # 强烈买入信号
                    signal = 1
                elif total_signal <= -2:
                    # 强烈卖出信号
                    signal = -1
                elif total_signal == 1:
                    # 轻微买入信号
                    signal = 1
                elif total_signal == -1:
                    # 轻微卖出信号
                    signal = -1
                
                # 检查持仓情况
                if position is not None:
                    stock_position = position[position['stock_code'] == stock_code]
                    if not stock_position.empty:
                        # 已有持仓
                        if signal == 1:
                            # 检查是否达到最大持仓比例
                            current_position_ratio = stock_position['market_value'].iloc[0] / position['market_value'].sum()
                            if current_position_ratio >= self.max_position_per_stock:
                                signal = 0  # 已达到最大持仓，取消买入信号
                    else:
                        # 无持仓
                        if signal == -1:
                            signal = 0  # 无持仓，取消卖出信号
                
                # 生成交易信号
                if signal != 0:
                    price = latest_stock_data.get('close', latest_stock_data.get('price', 0))
                    if price > 0:
                        # 计算交易数量
                        quantity = int(TRADE_CONFIG['order_amount'] / price)
                        if quantity > 0:
                            signals[stock_code] = {
                                'signal': signal,
                                'price': price,
                                'quantity': quantity
                            }
            
            strategy_logger.info(f"生成交易信号成功，信号数量: {len(signals)}")
            return signals
        except Exception as e:
            strategy_logger.error(f"生成交易信号失败: {str(e)}")
            return {}
    
    def evaluate_strategy(self, data, initial_capital=100000):
        """回测策略表现
        
        Args:
            data: DataFrame，包含价格和技术指标数据
            initial_capital: 初始资金
            
        Returns:
            dict: 策略表现评估结果
        """
        try:
            # 初始化回测数据
            backtest_data = data.copy()
            backtest_data['position'] = 0
            backtest_data['cash'] = initial_capital
            backtest_data['holdings'] = 0
            backtest_data['total'] = initial_capital
            
            # 模拟交易
            for i in range(1, len(backtest_data)):
                # 生成交易信号
                signal = backtest_data.iloc[i-1].get('total_signal', 0)
                
                # 执行交易
                if signal >= 1 and backtest_data.iloc[i-1]['position'] == 0:
                    # 买入
                    price = backtest_data.iloc[i]['close']
                    quantity = int(backtest_data.iloc[i-1]['cash'] / price)
                    backtest_data.loc[backtest_data.index[i], 'position'] = quantity
                    backtest_data.loc[backtest_data.index[i], 'cash'] = backtest_data.iloc[i-1]['cash'] - quantity * price
                elif signal <= -1 and backtest_data.iloc[i-1]['position'] > 0:
                    # 卖出
                    price = backtest_data.iloc[i]['close']
                    quantity = backtest_data.iloc[i-1]['position']
                    backtest_data.loc[backtest_data.index[i], 'position'] = 0
                    backtest_data.loc[backtest_data.index[i], 'cash'] = backtest_data.iloc[i-1]['cash'] + quantity * price
                else:
                    # 持有不变
                    backtest_data.loc[backtest_data.index[i], 'position'] = backtest_data.iloc[i-1]['position']
                    backtest_data.loc[backtest_data.index[i], 'cash'] = backtest_data.iloc[i-1]['cash']
                
                # 计算持仓价值和总价值
                backtest_data.loc[backtest_data.index[i], 'holdings'] = backtest_data.loc[backtest_data.index[i], 'position'] * backtest_data.iloc[i]['close']
                backtest_data.loc[backtest_data.index[i], 'total'] = backtest_data.loc[backtest_data.index[i], 'cash'] + backtest_data.loc[backtest_data.index[i], 'holdings']
            
            # 计算策略表现指标
            total_return = (backtest_data.iloc[-1]['total'] - initial_capital) / initial_capital
            max_drawdown = ((backtest_data['total'].cummax() - backtest_data['total']) / backtest_data['total'].cummax()).max()
            sharpe_ratio = (backtest_data['total'].pct_change().mean() / backtest_data['total'].pct_change().std()) * (252 ** 0.5) if backtest_data['total'].pct_change().std() > 0 else 0
            
            performance = {
                'total_return': total_return,
                'max_drawdown': max_drawdown,
                'sharpe_ratio': sharpe_ratio,
                'final_value': backtest_data.iloc[-1]['total'],
                'trades': len(backtest_data[backtest_data['position'] != backtest_data['position'].shift()]) - 1
            }
            
            strategy_logger.info(f"回测策略表现成功，总收益率: {total_return:.2%}，最大回撤: {max_drawdown:.2%}，夏普比率: {sharpe_ratio:.2f}")
            return performance
        except Exception as e:
            strategy_logger.error(f"回测策略表现失败: {str(e)}")
            return {}
