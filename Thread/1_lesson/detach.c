#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *th_start(void *arg)
{
    printf("hello world!\n");
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, th_start, NULL);
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }
    //不会阻塞, 只是设置了一个属性
    pthread_detach(tid);
}
