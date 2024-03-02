#include <stdio.h>
#include <sys/mman.h>

void main(void)
{
    char *pmap1, *pmap2;

    pmap1 = (char *)mmap(0x20000000, 10240, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
    if(MAP_FAILED == pmap1)
        printf("pmap1 failed\n");

    pmap2 = (char *)mmap(0x20000000, 1024, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
    if(MAP_FAILED == pmap2)
        printf("pmap1 failed\n");
}

