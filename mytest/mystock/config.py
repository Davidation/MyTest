# 系统配置文件

# 同花顺API配置
THS_API_CONFIG = {
    'app_key': 'your_',  # 替换为实际的App Key
    'app_secret': 'your_app_secret',  # 替换为实际的App Secret
    'account_id': 'your_account_id',  # 替换为实际的账户ID
    'password': 'your_password',  # 替换为实际的密码
    'base_url': 'https://openapi.ths.com/v1',  # 同花顺OpenAPI基础URL
    'timeout': 10,  # API请求超时时间(秒)
}

# 交易配置
TRADE_CONFIG = {
    'max_position_per_stock': 0.3,  # 单只股票最大持仓比例
    'max_daily_trades': 10,  # 每日最大交易次数
    'stop_loss_ratio': 0.05,  # 止损比例
    'take_profit_ratio': 0.1,  # 止盈比例
    'order_amount': 10000,  # 每次下单金额(元)
    'trade_hours': {
        'morning_start': '09:30',
        'morning_end': '11:30',
        'afternoon_start': '13:00',
        'afternoon_end': '20:00',
    },
}

# 技术指标配置
TECHNICAL_INDICATORS = {
    'ma': {
        'short_period': 10,  # 短期移动平均线周期
        'long_period': 30,  # 长期移动平均线周期
    },
    'macd': {
        'fast_period': 12,  # MACD快速线周期
        'slow_period': 26,  # MACD慢速线周期
        'signal_period': 9,  # MACD信号线周期
    },
    'rsi': {
        'period': 14,  # RSI周期
        'overbought': 70,  # 超买阈值
        'oversold': 30,  # 超卖阈值
    },
}

# 策略配置
STRATEGY_CONFIG = {
    'strategy_name': 'MA_MACD_RSI',  # 默认策略名称
    'lookback_period': 60,  # 回溯周期(天)
    'signal_threshold': 0.5,  # 信号阈值
    'min_holding_period': 1,  # 最小持有周期(天)
}

# 日志配置
LOG_CONFIG = {
    'log_dir': 'logs',  # 日志目录
    'log_level': 'INFO',  # 日志级别
    'max_log_size': 10485760,  # 最大日志文件大小(10MB)
    'backup_count': 5,  # 日志文件备份数量
}

# 股票池配置
STOCK_POOL = [
    '600000.SH',  # 浦发银行
    '600519.SH',  # 贵州茅台
    '000858.SZ',  # 五粮液
    '000001.SZ',  # 平安银行
    '601318.SH',  # 中国平安
    # 可根据需要添加更多股票
]
