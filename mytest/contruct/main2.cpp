#include <cstdlib>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <cstdio>
#include <string.h>
 
 
class CMyString {
private:
	char * buf;
	int len;
 
private:
	void copy(const char* s) {
		buf = new char[len+1];
		memcpy(buf, s, len);
		buf[len] = '\0';
	}
 
public:
	CMyString() {
		std::cout << "���캯��" << " LINE " << __LINE__ << std::endl;
 
		buf = nullptr;
		len = 0;
	}
 
	CMyString(const char* str = nullptr) {
		if (str == nullptr) {
			std::cout << "���캯��" << " LINE " << __LINE__ << std::endl;
 
			buf = nullptr;
			len = 0;
		}
		else {
			std::cout << "���캯��" << str << " LINE " << __LINE__ << std::endl;
			len = strlen(str);
			copy(str);
		}
	}
 
	CMyString(const CMyString& str) {
		std::cout << "�������캯��" << str.buf << " LINE " << __LINE__ << std::endl;
 
		len = str.len;
		copy(str.buf);		
	}
 
	CMyString(CMyString&& str) {
		std::cout << "�ƶ����캯��" << str.buf << " LINE " << __LINE__ << std::endl;
 
		//Ҳ����ֱ��ʹ��std::move
 
		len = str.len;
		buf = str.buf;
 
		
 
		str.len = 0;
		str.buf = nullptr;
	}
 
	CMyString& operator=(const CMyString& str) {
		std::cout << "������ֵ����" << str.buf << " LINE " << __LINE__ << std::endl;
 
		if (&str != this) {
			if (buf != nullptr) {
				delete[] buf;
				buf = nullptr;
			}
 
			len = str.len;
			copy(str.buf);
		}
 
		return *this;
	}
 
	
 
	CMyString& operator=(CMyString&& str) {
		std::cout << "�ƶ���ֵ����" << str.buf << " LINE " << __LINE__ << std::endl;
 
		if (this != &str) {
 
			if (buf != nullptr) {
				delete[] buf;
				buf = nullptr;
			}
 
			len = str.len;
			buf = str.buf;
			str.len = 0;
			str.buf = nullptr;
		}
 
		return *this;
	}
 
	~CMyString() {
		if (buf == nullptr)
		{
			std::cout << "��������" << " LINE " << __LINE__ << std::endl;
		}
		else
		{
			std::cout << "��������" << buf << " LINE " << __LINE__ << std::endl;
			delete[] buf;
			buf = nullptr;
		}
	}
 
	void print() {
		if (buf != nullptr)
			std::cout << buf << " LINE " << __LINE__ << std::endl;
		else
			std::cout << "buf is null" << " LINE " << __LINE__ << std::endl;
	}
 
	
};
 
void func1(CMyString str) {
	
}
 
CMyString func2() {
	CMyString s("34");
	return s;
}
 
void test0() {
	CMyString s1("12");
 
	func1(s1); //����str��δ��ʼ��������ÿ������캯��
 
	CMyString s2 = func2(); // ����s2��δ��ʼ�����������ʱ���󣬵����ƶ����캯��
 
 
	CMyString s3 = "56";
 
	s3 = s1; //����s3�ѳ�ʼ��������ÿ�����ֵ����
}
 
void test1() {
	CMyString s4 = "78";
	std::vector<CMyString> v1;
	//v1.push_back(s4);
	v1.push_back(std::move(s4)); // ������δ��ʼ����������ƶ����캯��
 
	std::cout << "��ʼ���v1\n";
	for (auto& str : v1)
		str.print();
 
	std::vector<CMyString> v2;
	v2 = std::move(v1);
 
	std::cout << "��ʼ���v1\n";
	for (auto& str : v1)
		str.print();
 
	std::cout << "��ʼ���v2\n";
	for (auto& str : v2)
		str.print();
}
 
void test2() {
	
	CMyString s5 = "9";
	s5 = func2(); // ����s5�ѳ�ʼ���� �������ʱ���󣬵����ƶ���ֵ����
}
 
int main(void)
{	
	std::cout << "begin test0()" << std::endl;
	test0();
	std::cout << std::endl;
 
	std::cout << "begin test1()" << std::endl;
	test1();
	std::cout << std::endl;
 
	std::cout << "begin test2()" << std::endl;
	test2();
 
	return 0;
}

/*
begin test0()
���캯��12 LINE 38
�������캯��12 LINE 45
��������12 LINE 109
���캯��34 LINE 38
���캯��56 LINE 38
������ֵ����12 LINE 66
��������12 LINE 109
��������34 LINE 109
��������12 LINE 109

begin test1()
���캯��78 LINE 38
�ƶ����캯��78 LINE 52
��ʼ���v1
78 LINE 117
��ʼ���v1
��ʼ���v2
78 LINE 117
��������78 LINE 109
�������� LINE 105

begin test2()
���캯��9 LINE 38
���캯��34 LINE 38
�ƶ���ֵ����34 LINE 84
�������� LINE 105
��������34 LINE 109
*/
