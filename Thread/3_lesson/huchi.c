/*使用信号量实现互斥*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;
int ticket = 100;

void *buy_ticket(void *arg)
{
    while(1){
        //计数器最大是1，只有一个线程能获取到信号量
        //这也就保证了在同一时间至于一个线程能操作
        sem_wait(&sem);
        if(ticket > 0){
            usleep(1000);
            ticket--;
            printf("cow %lu, buy a ticket:%d\n", ticket);
        }
        //操作完毕计数器+1，信号量资源技术可以获取
        sem_post(&sem);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret, i;
    ret = sem_init(&sem, 0, 1);
    if(ret < 0){
        perror("sem_init");
        return -1;
    }

    for(i = 0; i < 4; i++){
        ret = pthread_create(&tid, NULL, buy_ticket, NULL); //买票
        if(ret != 0){
            perror("pthread_create");
            return -1;
        }
    }

    pthread_join(tid, NULL);
    //sem_destroy(&sem);
    return 0;
}
