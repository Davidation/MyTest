#include <stdio.h>
#include <cstring>
#include <boost/context/detail/fcontext.hpp>

boost::context::detail::transfer_t main_tf;
boost::context::detail::transfer_t foo1_tf;
boost::context::detail::transfer_t foo2_tf;

//static char foo_stack1[4096];

char *stack1;
char *foo_stack1;

int z = 0;


void foo_fn1(boost::context::detail::transfer_t t)
{
	int *x = (int *)t.data;

    printf("f1 begin %d %lx\n", *x, t.fctx);

	z = 2;
	printf("bbb %lx", (void *)t.fctx);
    main_tf = boost::context::detail::jump_fcontext(t.fctx, &z);

	int *y = (int *)t.data;
    printf("back f1 %d %d %lx %lx\n", *x, *y, t.fctx, main_tf.fctx);

	// ע�����ﲻ����t.fctx��������main_tf.fctx������Ϊʲô�������������е�printf
	// ��Ϊ��z=3��������ʱ����Ȼ������һ������rdi�Ĵ����ͷ���ֵrax��ȣ�����������z=2�����ŷ���ֵ�������β�t��������rdi����һ�ε��β�t����ջ�ϴ���������ÿ��jump��ʱ�򣬻����ٵ�һ�����ڵ�fctx��
	// ���ԣ��������κ�һ��fctx�����ܱ�jump���Σ�����Ҫ���º������jump
	z = 4;
    main_tf = boost::context::detail::jump_fcontext(main_tf.fctx, &z);
    printf("f1 end \n");
}

void foo()
{
   	printf("start foo\n");
	z = 1;
    foo1_tf = boost::context::detail::jump_fcontext(foo1_tf.fctx, &z);

    printf("back foo \n");
	

    printf("end foo\n");
}

int main()
{
    printf("start main\n");

	stack1 = (char *)malloc(40960);

	foo_stack1 = stack1;

	foo_stack1 = (char *)((long int)(foo_stack1 + 511) & 0xfffffffffffffff0);

	foo1_tf.fctx = boost::context::detail::make_fcontext(foo_stack1, 512, foo_fn1);

	printf("stack1 %lx to %lx, make ret addr %lx should %lx\n"
			, stack1, foo_stack1, (char *)foo1_tf.fctx, foo_stack1 - 0x48);

	foo();

	z = 3;
    foo1_tf = boost::context::detail::jump_fcontext(foo1_tf.fctx, &z);


	free(stack1);

    printf("end main\n");

    return 0;
}


//stack1 bf42c0 to bf44b0, stack2 bfe2d0 to bfe4c0 make ret addr bf4468 should bf4468


/*output:

start main
stack1 18512c0 to 18514b0, make ret addr 1851468 should 1851468
start foo
f1 begin 1 7ffe701f17b8
back foo
end foo
back f1 3 3 7ffe701f17b8 7ffe701f17c8
end main

*/
