#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>

int main(int argc, char **argv)
{
    key_t key = ftok("/dev/shm/myshm", 0);
    int shm_id = shmget(key, 0x400000, IPC_CREAT | 0666); //建立 Shared Memory
    int *p = (int *) shmat(shm_id, NULL, 0); //將共享記憶體 mapping 到指標
    while(1)
    {

        /*
        p[0]、p[1]用來存放輸入的兩個整數

        p[2]用來存放p[0]、p[1]相加的結果

        p[3]用來判斷資料狀態 :
        0 : 使用者尚未輸入資料
        1 : 資料已輸入，但process2尚未計算
        2 : 已將結果寫入shared memory
        */
        p[3]=0; 
        printf("Please input two integers:");
        scanf("%d %d",&p[0],&p[1]);
        p[3]=1;
        while(p[3]!=2); //等待p2讀取資料並寫入結果
        printf("%d\n",p[2]);
        p[3]=0;
    }
    
    return 0;
}