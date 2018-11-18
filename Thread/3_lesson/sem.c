/*  信号量实现线程同步
 *  信号量初始化
 *  信号量操作
 *  信号量释放
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;

void *thr_pro(void *arg)
{
    while(1){
        // product
        // sem_post, 生产资源后通知等待在信号量上的线程
        // 信号量修改内部资源计数器，使用更加简单
        // 条件变量修改的是外部条件，需要用户自己修改
        sleep(1);
        printf("make things!\n");
        sem_post(&sem);
    }
    return NULL;
}

void *thr_cur(void *arg)
{
    while(1){
        // consum
        // 没有资源，等待
        sem_wait(&sem);
        printf("use thing!\n");
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    int ret;

    ret = sem_init(&sem, 0, 0); //初始化信号量, 第二个参数为0是用于线程，非0进程
    if(ret < 0){
        perror("sem_init");
        return -1;
    }

    ret = pthread_create(&tid1, NULL, thr_pro, NULL); //producter
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }

    ret = pthread_create(&tid2, NULL, thr_cur, NULL); //consumer
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&sem); //信号量销毁
    return 0;
}
