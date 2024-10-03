from utils import read_file, assert_msg, crossover, SMA

class ExchangeAPI:
    def __init__(self, data, cash, commission):
        assert_msg(0 < cash, "��ʼ�ֽ���������0��������ֽ�������{}".format(cash))
        assert_msg(0 <= commission <= 0.05, "�������������һ�㲻�ᳬ��5%������ķ��ʣ�{}".format(commission))
        self._inital_cash = cash
        self._data = data
        self._commission = commission
        self._position = 0
        self._cash = cash
        self._i = 0

    @property
    def cash(self):
        """
        :return: ���ص�ǰ�˻��ֽ�����
        """
        return self._cash

    @property
    def position(self):
        """
        :return: ���ص�ǰ�˻���λ
        """
        return self._position

    @property
    def initial_cash(self):
        """
        :return: ���س�ʼ�ֽ�����
        """
        return self._inital_cash

    @property
    def market_value(self):
        """
        :return: ���ص�ǰ��ֵ
        """
        return self._cash + self._position * self.current_price

    @property
    def current_price(self):
        """
        :return: ���ص�ǰ�г��۸�
        """
        return self._data.Close[self._i]

    def buy(self):
        """
        �õ�ǰ�˻�ʣ���ʽ𣬰����г��۸�ȫ������
        """
        self._position = float(self._cash / (self.current_price * (1 + self._commission)))
        self._cash = 0.0

    def sell(self):
        """
        ������ǰ�˻�ʣ��ֲ�
        """
        self._cash += float(self._position * self.current_price * (1 - self._commission))
        self._position = 0.0

    def next(self, tick):
        self._i = tick

