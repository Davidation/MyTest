

import abc
import numpy as np
from typing import Callable

class Strategy(metaclass=abc.ABCMeta):
    """
    ��������࣬���ڶ��彻�ײ��ԡ�

    ���Ҫ�����Լ��Ĳ����࣬��Ҫ�̳�������࣬��ʵ���������󷽷���
    Strategy.init
    Strategy.next
    """
    def __init__(self, broker, data):
        """
        ������Զ���

        @params broker:  ExchangeAPI    ����API�ӿڣ�����ģ�⽻��
        @params data:    list           ������������
        """
        self._indicators = []
        self._broker = broker  # type: _Broker
        self._data = data  # type: _Data
        self._tick = 0

    def I(self, func: Callable, *args) -> np.ndarray:
        """
        ��������ָ������������ָ��������һ�����飬���Ⱥ���ʷ���ݶ�Ӧ��
        �����ж����ʱ�������Ҫ����"��"����"��"��

        ������㻬��ƽ����
        def init():
            self.sma = self.I(utils.SMA, self.data.Close, N)
        """
        value = func(*args)
        value = np.asarray(value)
        assert_msg(value.shape[-1] == len(self._data.Close), 'ָʾ�����ȱ����data������ͬ')

        self._indicators.append(value)
        return value

    @property
    def tick(self):
        return self._tick

    @abc.abstractmethod
    def init(self):
        """
        ��ʼ�����ԡ��ڲ��Իز�/ִ�й����е���һ�Σ����ڳ�ʼ�������ڲ�״̬��
        ����Ҳ����Ԥ������Եĸ������������������ʷ�������ݣ�
        ����������ָʾ��������
        ѵ��ģ��/��ʼ��ģ�Ͳ���
        """
        pass

    @abc.abstractmethod
    def next(self, tick):
        """
        ����������ִ�е�tick���Ĳ��ԡ�tick����ǰ��"ʱ��"������data[tick]���ڷ��ʵ�ǰ���г��۸�
        """
        pass

    def buy(self):
        self._broker.buy()

    def sell(self):
        self._broker.sell()

    @property
    def data(self):
        return self._data


    def next(self, tick):
        # �����ʱ���߸պ�Խ�����ߣ�����ȫ��
        if crossover(self.sma1[:tick], self.sma2[:tick]):
            self.buy()

        # ��������߸պ�Խ�����ߣ�����ȫ��
        elif crossover(self.sma2[:tick], self.sma1[:tick]):
            self.sell()

        # �������ʱ�̲�ִ���κβ�����
        else:
            pass

def SMA(values, n):
    """
    ���ؼ򵥻���ƽ��
    """
    return pd.Series(values).rolling(n).mean()

def crossover(series1, series2) -> bool:
    """
    ������������Ƿ��ڽ�β����
    :param series1:  ����1
    :param series2:  ����2
    :return:         ������淵��True����֮False
    """
    return series1[-2] < series2[-2] and series1[-1] > series2[-1]


from utils import assert_msg, crossover, SMA

class SmaCross(Strategy):
    # С����SMA�Ĵ��ڴ�С�����ڼ���SMA����
    fast = 10

    # �󴰿�SMA�Ĵ��ڴ�С�����ڼ���SMA����
    slow = 20

    def init(self):
        # ������ʷ��ÿ��ʱ�̵Ŀ��ߺ�����
        self.sma1 = self.I(SMA, self.data.Close, self.fast)
        self.sma2 = self.I(SMA, self.data.Close, self.slow)

    def next(self, tick):
        # �����ʱ���߸պ�Խ�����ߣ�����ȫ��
        if crossover(self.sma1[:tick], self.sma2[:tick]):
            self.buy()

        # ��������߸պ�Խ�����ߣ�����ȫ��
        elif crossover(self.sma2[:tick], self.sma1[:tick]):
            self.sell()

        # �������ʱ�̲�ִ���κβ�����
        else:
            pass

