#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

static ucontext_t uctx_main, uctx_func1, uctx_func2;

#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void func1(void)
{
   printf("func1\n");
   if (swapcontext(&uctx_func1, &uctx_func2) == -1)
       handle_error("swapcontext");
   printf("func1 after\n");
}

static void func2(void)
{
   printf("func2\n");
   if (swapcontext(&uctx_func2, &uctx_func1) == -1)
       handle_error("swapcontext");
   printf("func2 after\n");
}

int main(int argc, char *argv[])
{
   char func1_stack[16384];
   char func2_stack[16384];
    // ���浱ǰ��ִ��������
   if (getcontext(&uctx_func1) == -1)
       handle_error("getcontext");

   // �����µ�ջ
   uctx_func1.uc_stack.ss_sp = func1_stack;
   uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
   // uctx_func1��Ӧ��Э��ִ����ִ��uctx_main
   uctx_func1.uc_link = &uctx_main;
   // ����Э���Ĺ�������
   makecontext(&uctx_func1, func1, 0);
   // ͬ��
   if (getcontext(&uctx_func2) == -1)
       handle_error("getcontext");
   uctx_func2.uc_stack.ss_sp = func2_stack;
   uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
   // uctx_func2ִ����ִ��uctx_func1
   uctx_func2.uc_link = (argc > 1) ? NULL : &uctx_func1;
   makecontext(&uctx_func2, func2, 0);
   // ���浱ǰִ�������ĵ�uctx_main��Ȼ��ʼִ��uctx_func2��Ӧ��������
    if (swapcontext(&uctx_main, &uctx_func2) == -1)
       handle_error("swapcontext");

   printf("main: exiting\n");
   exit(EXIT_SUCCESS);
}


