#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdio>

using namespace std;

struct BASE
{
public:
    int a;

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

    int b;
};

struct DE : virtual public BASE
{
    DE()
    {
        cout << "DE" << endl;
    }

    DE(int i):BASE(i)
    {
        cout << "DE " << i << endl;
        de = i - 1;
        b = i - 1;
    }

    ~DE()
    {
        cout << "~DE" << endl;
    }

private:
    int de;
};

struct DE2 : virtual public BASE
{
    DE2()
    {
        cout << "DE2" << endl;
    }

    DE2(int i):BASE(i)
    {
        cout << "DE2 " << i << endl;
        de2 = i + 1;
        b = i + 1;
    }

    ~DE2()
    {
        cout << "~DE2" << endl;
    }

    int de2;
};


struct D : private DE, public DE2
{
    D()
    {
        cout << "D" << endl;
    }

    D(int i): DE(i), DE2(i)
    {
        cout << "D " << i  << "b " << b << endl;
    }

    ~D()
    {
        cout << "~D" << endl;
    }

    int d;
};


int main()
{
    D aaa(3);
    cout << "main" << endl;

    
    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表


