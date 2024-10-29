#include <stdio.h>
#include "temp.h"

int printf(const char* format, ...);

int global_init_var = 84;

class MyClass{
public:

	MyClass()
	{
		global_init_var = 2;
	}

	~MyClass()
	{
		global_init_var = 3;
	}
};

MyClass c;
int main(void)
{
	int m = Max(8,9);
	float n = Max(1.2f,2.4f);

    return 0;
}
