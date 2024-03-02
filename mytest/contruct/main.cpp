#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdio>

using namespace std;

struct MEMBER
{
    MEMBER()
    {
        cout << "MEMBER" << endl;
    }

    ~MEMBER()
    {
        cout << "~MEMBER" << endl;
    }
};

struct DE_MEMBER
{
    DE_MEMBER()
    {
        cout << "DE_MEMBER" << endl;
    }

    ~DE_MEMBER()
    {
        cout << "~DE_MEMBER" << endl;
    }
};


struct BASE
{
public:
    int a;

    MEMBER e;
    BASE()
    {
        cout << "BASE" << endl;
    }

    BASE(int i)
    {
        cout << "BASE " << i << endl;
    }

    ~ BASE()
    {
        cout << "~BASE"  << endl;
    }
};

struct DE : public BASE
{
    DE_MEMBER b;

    DE()
    {
        cout << "DE" << endl;
    }

    DE(int i):BASE(i)
    {
        cout << "DE " << i << endl;
    }

    ~DE()
    {
        cout << "~DE" << endl;
    }
};

struct A
{
    BASE bb;
    DE d;
};

int test()
{
    A a;
}

int main()
{
    test();
    cout << "main" << endl;
    
    
    DE dd(2);

    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表


