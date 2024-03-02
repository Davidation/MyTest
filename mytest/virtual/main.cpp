#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

class BASE
{
public:
    virtual void fun_a(){cout << "BASE fun_a" << endl;}
    void fun_b(){cout << "BASE fun_b" << endl;}
    void base_func(){cout <<" base func" << endl;}

    int a;
};

class DE: public BASE
{
public:
    void fun_a()
    {
        //BASE::fun_a(); 
        cout << "DE fun_a" << endl;
    }
public:
    void fun_b(){cout << "DE fun_b" << endl;}

    int b;
    int c;
    int d[100000];

};

class PURE_BASE
{
public:
    virtual void func(int i = 1) = 0;
};

class PURE_DE
{
public:
    void func(int i = 1) {cout << "DE PURE_VIRTUAL " << i << endl;}
};

int main()
{
    BASE *b = new BASE();
    DE *d = new DE();
    BASE *db = new DE();

    d->fun_a();
    d->base_func();

    cout << "-----" << endl;

    db->fun_a();
    db->fun_b();

    cout << sizeof(BASE) << endl;
    cout << sizeof(DE) << endl;

    PURE_DE *P_D = new PURE_DE();
    P_D->func();

    int tmp = (int)sqrtf(-10);
    cout << tmp << endl;

    
    cout << "-----" << endl;
    DE *newd = new DE();
    newd->fun_a();
    cout << sizeof(*newd) << endl;


    BASE *newb = new (newd) BASE;
    newd->fun_a();
    newb->fun_a();
    cout << sizeof(*newd) << endl;
    cout << sizeof(*newb) << endl;

    cout << "-----" << endl;
    BASE *bbb = new BASE;
    DE *ddd = new(bbb) DE;
    ddd->fun_a();

    ddd->b = 2;
    cout << ddd->b << endl;

    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表
// 如果子类被父类placement new了，虚表就会重建为父类虚表
// 如果父类被子类placement new了，虚表就会重建为子类虚表,结果打印是正常的，不过因为子类比父类sizeof大，在父类地址上new真的没问题吗？

