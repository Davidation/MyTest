#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdio>
#include <typeinfo>
#include <memory>

using namespace std;

int main()
{
    int* rawPtr = new int(10);

    std::shared_ptr<int> sharedPtr(rawPtr);
    cout << sharedPtr.use_count() << endl;

    std::shared_ptr<int> sharedPtr2(rawPtr);
    cout << sharedPtr.use_count() << endl;

    std::shared_ptr<int> sharedPtr1 = sharedPtr; // ��ȷ�ķ�ʽ
    cout << sharedPtr.use_count() << endl;

    return 0;
}

// ����ʹ����ָ���ʼ������ָ�� ����ͬһ����ָ��ᴴ��������ƿ飬�ͷ�ʱ��Ҳ��double free
