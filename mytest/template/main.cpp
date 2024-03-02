#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <string.h>
#include <stdio.h>

using namespace std;

class AC
{
public:
    int a;
    int b;
    int c;
    static void ACFun(int a)
    {
        cout << a << endl;
        return;
    }
};

class B
{
public:
};



template<class T>
class TClass
{
public:
    int ta;

    void TFun()
    {
        T::ACFun(ta);
    }
};

int main()
{
    TClass<AC> tc;
    tc.ta = 4;
    tc.TFun();

    cout << tc.ta << endl;

    return 0;
}



