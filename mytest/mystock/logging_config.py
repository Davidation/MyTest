# 日志配置模块

import os
import logging
from logging.handlers import RotatingFileHandler
from config import LOG_CONFIG

# 确保日志目录存在
os.makedirs(LOG_CONFIG['log_dir'], exist_ok=True)

# 创建日志记录器
def setup_logger(name, log_file, level=logging.INFO):
    """设置日志记录器"""
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    
    # 文件处理器
    file_handler = RotatingFileHandler(
        log_file,
        maxBytes=LOG_CONFIG['max_log_size'],
        backupCount=LOG_CONFIG['backup_count']
    )
    file_handler.setFormatter(formatter)
    
    # 控制台处理器
    console_handler = logging.StreamHandler()
    console_handler.setFormatter(formatter)
    
    # 创建记录器
    logger = logging.getLogger(name)
    logger.setLevel(level)
    logger.addHandler(file_handler)
    logger.addHandler(console_handler)
    
    return logger

# 交易日志
trade_logger = setup_logger('trade', os.path.join(LOG_CONFIG['log_dir'], 'trade.log'))

# 策略日志
strategy_logger = setup_logger('strategy', os.path.join(LOG_CONFIG['log_dir'], 'strategy.log'))

# 系统日志
system_logger = setup_logger('system', os.path.join(LOG_CONFIG['log_dir'], 'system.log'))

# 数据日志
data_logger = setup_logger('data', os.path.join(LOG_CONFIG['log_dir'], 'data.log'))
