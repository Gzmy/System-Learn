#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void* thr_start(void *arg)
{
    int num = (int)arg;
    while(1){
        printf("talk:%d\n", num);
        sleep(1);
    }
    return NULL;
}

int main()
{
    //create
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thr_start, (void*)999);
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }
    
    //获取调用线程的线程id
    printf("main pthdead if :%lu\n", pthread_self());
    printf("pthread id:%lu\n", tid);
    while(1){
        printf("---------------line-----------------\n");
        sleep(1);
    }

    return 0;
}
