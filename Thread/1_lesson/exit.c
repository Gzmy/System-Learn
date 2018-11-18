#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *th_start(void *arg)
{
    //在线程当中调用exit函数会怎样-------> 直接退出进程
    // 进程退出,进程中的所有线程也要退出
    //exit(0);
    
    //线程的退出演示1:return
    //return NULL;
    
    //线程的退出演示2,pthread_exit,
    //谁调用谁退出,退出线程
    //pthread_exit(NULL);
    
    //线程的退出演示3,pthread_cancel, 取消线程
    pthread_cancel(pthread_self());
    while(1){
        printf("child pthread!\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, th_start, NULL);
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }
    //pthread_exit(NULL); //主线程退出,可能造成僵尸线程
    while(1){
        printf("main thread!!\n");
        sleep(1);
    }
}
