#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdio>

using namespace std;

struct BASE
{
public:
    int test_fun();
    int a;
};

int BASE::test_fun()
{
    cout << "test_fun" << endl;
}

int main()
{
    BASE b;
    
    b.test_fun();
    float a = 4.5f;
    printf("a= %f, %d\n", a, (int)a);
    a = 4.4f;
    printf("a= %f, %d\n", a, (int)a);
    a = 4.99999999999f;
    printf("a= %f, %d\n", a, (int)a);

    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表


