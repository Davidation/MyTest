#include <iostream>
#include <cstdio>


using namespace std;

struct BASE
{
public:
    int test_fun(int i);
    int a;
};

int BASE::test_fun(int i)
{
    cout << "test_fun" << i  << endl;
    return i+1;
}

int main()
{
    BASE b;

    b.a = 3;
    b.test_fun(2);


    return 0;
}




