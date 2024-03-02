#include <stdio.h>

typedef struct
{
    int i;
    int num;
    int state;
} task;

#define crBegin(state) \
        switch (state) { case 0:

#define crReturn(state, ret) \
        (state) = __COUNTER__; return (ret); case __COUNTER__:

#define crEnd() \
        }

#define TEST_COUNTER printf("__COUNTER__=%d ", __COUNTER__)
#define TEST_COUNTER2 printf("__COUNTER2__=%d ", __COUNTER__)

int cb(task *t)
{
    int tmp = 0;
    crBegin(t->state);
    for (;;) {
        t->num = 1;
        for (t->i = 0; t->i < 3; t->i++) {
            crReturn(t->state, t->num);
            t->num += 1;
        }
    }
    crEnd();
}

int main()
{
    task t;
    int i;

    TEST_COUNTER;
    TEST_COUNTER2;
    TEST_COUNTER;
    TEST_COUNTER2;

    t.state = 1;

    for (i = 0; i < 5; i++) {
        printf("%d ", cb(&t));
    }
    return 0;
}
