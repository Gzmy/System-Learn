#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int ticket = 100;
pthread_mutex_t mutex; //定义互斥锁结构体

//初始化两种方式:
//  1.定义时直接赋值初始化,不需要手动释放   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//  2.函数接口初始化,需要手动释放



void *y_cow(void *arg)
{
    int id = (int)arg;
    while(1){
        //临界访问之前加锁操作
        //pthread_mutex_lock --阻塞加锁,获取不到锁则阻塞等待锁被解开
        //pthread_mutex_trylock --非阻塞加锁,获取不到锁则立即报错返回
        //pthread_mutex_timedlock --限时阻塞加锁,获取不到阻塞等待,在这段时间一直获取不到,报错返回
        pthread_mutex_lock(&mutex); //加锁
        if(ticket > 0){
            usleep(100);
            printf("y_cow : %d    get a ticket : %d\n", id, ticket);
            ticket--;
        }else{
            printf("y_cow:%d no ticket! exit\n", id);
            pthread_mutex_unlock(&mutex); //解锁, 在加锁后任意有可能退出的地方都要进行解锁,否则会导致其他线程阻塞
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex); //解锁
    }
    return NULL;
}

int main()
{
    pthread_t tid[4];
    int i = 0, ret;

    int tmp = pthread_mutex_init(&mutex, NULL); //互斥锁初始化
    if(tmp != 0){
        perror("pthread_mutex_init");
        return -1;
    }

    for(; i < 4; i++){
        ret = pthread_create(&tid[i], NULL, y_cow, (void*)i);
        if(ret < 0){
            perror("pthread_create");
            return -1;
        }
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);

    pthread_mutex_destroy(&mutex); //销毁互斥锁
    return 0;
}
