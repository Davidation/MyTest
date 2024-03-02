#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>

unsigned int key = 0x12345;
size_t shmsize = 72999999999;

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        key = atoi(argv[1]);
    }

    int shm_id = shmget(key, shmsize, 0666 | IPC_CREAT | IPC_EXCL);
    if(shm_id <= 0)
    {
        printf("failed\n");
        return 0;
    }

    void *pool = shmat(shm_id, NULL, 0);
    if(pool <= 0)
    {
        printf("failed\n");
        return 0;
    }

    printf("key %u %x id %d\n", key ,key , shm_id); 

    //sleep(1200);
    sleep(5);

    long unsigned int *p = (long unsigned int *)pool;

    printf("start addr %lu\n", &p[0]);
    long unsigned int i = 0;
    for(i = 0; i < shmsize / 8 -1; ++i)
    {
        p[i] = i;
    }

    printf("end addr %lu,value %lu\n", &p[i], i);

    shmctl(shm_id, IPC_RMID, 0);

    printf("key %u %x id %d remove\n", key , key, shm_id); 
}

