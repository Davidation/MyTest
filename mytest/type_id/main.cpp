#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdio>
#include <typeinfo>

using namespace std;

template <class T>
struct BASE
{
    int a;

public:
    int test_fun();
};

template <class T>
int BASE<T>::test_fun()
{
    cout << "my test_fun" << endl;
    //cout << __function__ << endl;
    cout << __FUNCTION__ << endl;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << typeid(T).name() << endl;
}

struct AAA
{
    AAA  & a;
    char i[8];
    ///int print()
    ///{ 
    ///    cout  << typeid(a).name() << endl;
    ///}

};

struct BBB
{
    char i[8];
};


int main()
{
    BASE<AAA> b;
    
    b.test_fun();
    float a = 4.5f;
    printf("a= %f, %d\n", a, (int)a);
    a = 4.4f;
    printf("a= %f, %d\n", a, (int)a);
    a = 4.99999999999f;
    printf("a= %f, %d\n", a, (int)a);

    cout << typeid(b).name() << endl;
    
    //AAA aa;

    BBB bb;
    cout << sizeof(AAA) << endl;
    cout << sizeof(bb) << endl;

    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表


