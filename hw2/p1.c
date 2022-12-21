#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>

int main(int argc, char **argv)
{
    key_t key = ftok("/dev/shm", 0);
    int shm_id = shmget(key, 0x400000, IPC_CREAT | 0666); //建立 Shared Memory
    int *p = (int *) shmat(shm_id, NULL, 0); //將共享記憶體 mapping 到指標
    while(1)
    {
        p[0]=0; 
        printf("Please input two integers:");
        scanf("%d %d",&p[1],&p[2]);
        p[0]=1;
        while(p[0]!=2); //等待p2讀取資料並寫入結果
        printf("%d\n",p[3]);
        p[0]=0;
    }
    
    return 0;
}
