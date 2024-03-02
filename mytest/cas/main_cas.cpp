#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>

static int cas(int *ptr, int cmp, int new_val)
{
	int old_value = *ptr;
	__asm__ volatile("lock; cmpxchg %2, %3"
						: "=a" (old_value), "=m" (*ptr)
						: "r" (new_val), "m" (*ptr), "0" (cmp)
						: "cc", "memory");
	return old_value;
}

int main()
{
	int a = 0;
	for(int i = 0; i < 100; ++i)
	{
		cas(&a, a, a+1);
	}

	std::cout << a << std::endl;
    return 0;
}

/*
	// 四行分别是：
	__asm__ volatile("lock; cmpxchg %2, %3"
						: "=a" (old_value), "=m" (*ptr)
						: "r" (new_val), "m" (*ptr), "0" (cmp)
						: "cc", "memory");
	汇编代码，输出部分，输入部分，会被修改的部分

	cmpxchg %ebx, %ecx的意思是：如果eax(%0)与ecx(%3)相等，则将ebx（%2）的值送入到ecx(%3)。
*/


