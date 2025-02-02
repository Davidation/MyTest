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

    std::shared_ptr<int> sharedPtr1 = sharedPtr; // 正确的方式
    cout << sharedPtr.use_count() << endl;

    return 0;
}

// 不能使用裸指针初始化智能指针 否则同一个裸指针会创建多个控制块，释放时候也会double free
