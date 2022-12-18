#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    key_t key = ftok("/dev/shm/myshm", 0);
    int shm_id = shmget(key, 0x400000, 0666); //取得/建立 Shared Memory
    int *p = (int *) shmat(shm_id, NULL, 0);  //將共享記憶體 mapping 到指標
    while(1)
    {
        if(p[3]==1)
        {
            p[2] = p[0]+p[1];
            printf("The calculation is completed");
            p[3]=2;
        }
        
    }
    return 0;
}