#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <string.h>
#include <stdio.h>

using namespace std;

struct AC
{
    int a;
    int b;
    int c;
};


int main()
{
    int A[5] = {1,2,3,4,5};
    
    memmove(&A[1], &A[3], sizeof(A[0]) * 2);

    for(int i = 0;i < 5; ++i)
    {
        cout <<A[i] << " ";
    }

    cout << endl;

    int (*pA1)[5] = &A;
    int *pA2 = &A[0];

    printf("A1:%x, A1+1:%x\n", pA1, pA1+1);
    printf("A2:%x, A2+1:%x\n", pA2, pA2+1);

    int a;
    int *pi = &a;
    printf("a:%x, a+1:%x\n", pi, pi+1);
    
    AC ac;
    AC *pa = &ac;
    printf("ac:%x, ac+1:%x\n", pa, pa+1);

    return 0;
}


// 有virtual 虚函数，才会有虚表。
// 即使有继承关系，只要没有虚函数，就不会有虚表


