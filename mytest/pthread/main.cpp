#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>


using namespace std;

void print_info(char *ext_info = NULL)
{
	int i = 1;
	int *p = (int *)malloc(sizeof(int));
	
	cout << "cur info for :" ;
	if(ext_info != NULL)
	{
		cout << ext_info;
	}

	cout << endl;
	cout << "    getpid: " << getpid() << endl;
	cout << "    getppid: " << getppid() << endl;
	cout << "    syscall gettid: " << syscall(SYS_gettid) << endl;
	cout << "    pthread_self: " << pthread_self() << endl;
	cout << "    stack addr: " << &i << endl;
	cout << "    heap addr: " << p << endl;
	cout << endl;

	free(p);
}

void* thread(void * val)
{
	print_info();

	int* p_val= (int* )val;

	int preval = *p_val;

	*p_val += 1;

	cout << "val change from " << preval << " to " << *p_val << endl;

	pthread_exit((void *)"pthread exit");
}

int main()
{
	print_info("main");

	pthread_t id1, id2;
	int val, ret;
	ret = pthread_create(&id1, NULL, thread, &val); 
	if(ret != 0)
	{
		cout << "create p1 error" << endl;
		exit(1);
	}

	usleep(1000000);
	ret = pthread_create(&id2, NULL, thread, &val);
	if(ret != 0)
	{
		cout << "create p2 error" << endl;
		exit(1);
	}

	void *a;
	pthread_join(id1, &a); // 子线程即使已经执行结束了，主线程还是可以join。一般情况也确实是主线程要等子线程结束才结束
	cout << "get id1 exit return -- " << (char*)a << endl;

	pthread_join(id2, &a);
	cout << "get id2 exit return -- " << (char*)a << endl;


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


/*
	pthread创建的线程的栈通过mmap在进程的内存映射区，线程栈是不共享的，应该只到创建线程的方法那层（更上层比如main的堆栈，线程栈共享的，不然栈也太深了）
	如果把主线程的栈变量地址传到子线程，子线程对其解引用操作，实际操作的是同一个变量

	pthread创建的线程的堆也是在内存映射区，和主线程不一样的是，主线程的堆向上增长，子线程的堆在内存映射区向下增长，这里引入了arena的概念:
	https://www.ascotbe.com/2021/05/04/HeapOverflow_Linux_0x01/#arena
*/

