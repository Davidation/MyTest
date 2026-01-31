# 技术指标计算模块

import pandas as pd
import numpy as np
from config import TECHNICAL_INDICATORS
from logging_config import strategy_logger

class TechnicalIndicators:
    """技术指标计算类"""
    
    def __init__(self):
        self.ma_config = TECHNICAL_INDICATORS['ma']
        self.macd_config = TECHNICAL_INDICATORS['macd']
        self.rsi_config = TECHNICAL_INDICATORS['rsi']
    
    def calculate_ma(self, data, price_column='close'):
        """计算移动平均线
        
        Args:
            data: DataFrame，包含价格数据
            price_column: 价格列名
            
        Returns:
            DataFrame: 包含移动平均线数据的DataFrame
        """
        try:
            df = data.copy()
            # 计算短期移动平均线
            short_period = self.ma_config['short_period']
            df[f'ma{short_period}'] = df[price_column].rolling(window=short_period).mean()
            
            # 计算长期移动平均线
            long_period = self.ma_config['long_period']
            df[f'ma{long_period}'] = df[price_column].rolling(window=long_period).mean()
            
            # 计算均线金叉死叉信号
            df['ma_signal'] = 0
            # 金叉：短期均线上穿长期均线
            df.loc[(df[f'ma{short_period}'] > df[f'ma{long_period}']) & 
                   (df[f'ma{short_period}'].shift(1) <= df[f'ma{long_period}'].shift(1)), 'ma_signal'] = 1
            # 死叉：短期均线下穿长期均线
            df.loc[(df[f'ma{short_period}'] < df[f'ma{long_period}']) & 
                   (df[f'ma{short_period}'].shift(1) >= df[f'ma{long_period}'].shift(1)), 'ma_signal'] = -1
            
            strategy_logger.info(f"计算移动平均线成功，短期周期: {short_period}，长期周期: {long_period}")
            return df
        except Exception as e:
            strategy_logger.error(f"计算移动平均线失败: {str(e)}")
            return data
    
    def calculate_macd(self, data, price_column='close'):
        """计算MACD指标
        
        Args:
            data: DataFrame，包含价格数据
            price_column: 价格列名
            
        Returns:
            DataFrame: 包含MACD数据的DataFrame
        """
        try:
            df = data.copy()
            fast_period = self.macd_config['fast_period']
            slow_period = self.macd_config['slow_period']
            signal_period = self.macd_config['signal_period']
            
            # 计算EMA
            df['ema_fast'] = df[price_column].ewm(span=fast_period, adjust=False).mean()
            df['ema_slow'] = df[price_column].ewm(span=slow_period, adjust=False).mean()
            
            # 计算DIF
            df['macd_dif'] = df['ema_fast'] - df['ema_slow']
            
            # 计算DEA
            df['macd_dea'] = df['macd_dif'].ewm(span=signal_period, adjust=False).mean()
            
            # 计算MACD柱状图
            df['macd_hist'] = 2 * (df['macd_dif'] - df['macd_dea'])
            
            # 计算MACD信号
            df['macd_signal'] = 0
            # 金叉：DIF上穿DEA
            df.loc[(df['macd_dif'] > df['macd_dea']) & 
                   (df['macd_dif'].shift(1) <= df['macd_dea'].shift(1)), 'macd_signal'] = 1
            # 死叉：DIF下穿DEA
            df.loc[(df['macd_dif'] < df['macd_dea']) & 
                   (df['macd_dif'].shift(1) >= df['macd_dea'].shift(1)), 'macd_signal'] = -1
            
            strategy_logger.info(f"计算MACD成功，参数: fast={fast_period}, slow={slow_period}, signal={signal_period}")
            return df
        except Exception as e:
            strategy_logger.error(f"计算MACD失败: {str(e)}")
            return data
    
    def calculate_rsi(self, data, price_column='close'):
        """计算RSI指标
        
        Args:
            data: DataFrame，包含价格数据
            price_column: 价格列名
            
        Returns:
            DataFrame: 包含RSI数据的DataFrame
        """
        try:
            df = data.copy()
            period = self.rsi_config['period']
            overbought = self.rsi_config['overbought']
            oversold = self.rsi_config['oversold']
            
            # 计算价格变化
            delta = df[price_column].diff()
            
            # 计算上涨和下跌
            gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
            loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
            
            # 计算RSI
            rs = gain / loss
            df['rsi'] = 100 - (100 / (1 + rs))
            
            # 计算RSI信号
            df['rsi_signal'] = 0
            # 超卖：RSI低于超卖阈值
            df.loc[df['rsi'] < oversold, 'rsi_signal'] = 1
            # 超买：RSI高于超买阈值
            df.loc[df['rsi'] > overbought, 'rsi_signal'] = -1
            
            strategy_logger.info(f"计算RSI成功，周期: {period}，超买阈值: {overbought}，超卖阈值: {oversold}")
            return df
        except Exception as e:
            strategy_logger.error(f"计算RSI失败: {str(e)}")
            return data
    
    def calculate_all_indicators(self, data, price_column='close'):
        """计算所有技术指标
        
        Args:
            data: DataFrame，包含价格数据
            price_column: 价格列名
            
        Returns:
            DataFrame: 包含所有技术指标数据的DataFrame
        """
        try:
            # 计算移动平均线
            df = self.calculate_ma(data, price_column)
            
            # 计算MACD
            df = self.calculate_macd(df, price_column)
            
            # 计算RSI
            df = self.calculate_rsi(df, price_column)
            
            # 综合信号
            df['total_signal'] = df['ma_signal'] + df['macd_signal'] + df['rsi_signal']
            
            strategy_logger.info("计算所有技术指标成功")
            return df
        except Exception as e:
            strategy_logger.error(f"计算所有技术指标失败: {str(e)}")
            return data
