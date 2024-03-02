#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <pthread.h>
#include <unistd.h>


using namespace std;

int num = 3;

static int cas(int *ptr, int cmp, int new_val)
{
	int old_value = *ptr;
	__asm__ volatile("lock; cmpxchg %2, %3"
						: "=a" (old_value), "=m" (*ptr)
						: "r" (new_val), "m" (*ptr), "0" (cmp)
						: "cc", "memory");
	return old_value;
}

void* thread(void * idx)
{
	int* p_idx = (int* )idx;
	int i ;

	char* s;
	if(*p_idx % 2 == 0)
	{
		s = "A";
	}
	else
	{
		s = "B";
	}

	for(i = 0; i < 1000; ++i)
	{
		int old = num;

		if(*p_idx % 2 == 0)
		{
			num++;
		}
		else
		{
			num--;
		}

		// 下面这两行打印接口 会让main函数最后打印的num值是正确的（按理说多线程竞争 不能的）,去掉就发现打印值不对了
		// 上面说法不对，这行打印加不加，最后打印的num值都有可能是不正确的
		cout << "this is thread " << s << " opt " << old << " to " << num << endl;
		//fflush(stdout);

		usleep(1);
	}

	pthread_exit((void *)"pthread exit");
}

int main()
{
	pthread_t id1, id2;
	void *a;
	int idx, aidx, ret;
	idx = 1;
	aidx = 1;
	ret = pthread_create(&id1, NULL, thread, &aidx); // 注意这里不是idx，而是aidx。如果是idx，p1打印出来的值总是后面的idx = 2
	if(ret != 0)
	{
		cout << "create p1 error" << endl;
		exit(1);
	}

	idx = 2;
	ret = pthread_create(&id2, NULL, thread, &idx);
	if(ret != 0)
	{
		cout << "create p2 error" << endl;
		exit(1);
	}

/*
	for(int i = 0; i < 5; ++i)
	{
		cout << "this is main process" << endl;
	}
*/
	pthread_join(id1, &a);
	cout << "get id1 exit return -- " << (char*)a << endl;

	pthread_join(id2, &a);
	cout << "get id2 exit return -- " << (char*)a << endl;


	cout << "main process exit with num " << num << endl;
    return 0;
}


/* 编译要加选项
g++ main_raw.cpp  -lpthread
*/

/*
	// 四行分别是：
	__asm__ volatile("lock; cmpxchg %2, %3"
						: "=a" (old_value), "=m" (*ptr)
						: "r" (new_val), "m" (*ptr), "0" (cmp)
						: "cc", "memory");
	汇编代码，输出部分，输入部分，会被修改的部分

	cmpxchg %ebx, %ecx的意思是：如果eax(%0)与ecx(%3)相等，则将ebx（%2）的值送入到ecx(%3)。
*/



