//生产者与消费者简单同步代码

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//定义条件变量
pthread_cond_t cond;
pthread_mutex_t mutex;
int basket = 0;

//pthread_cond_init--初始化条件变量

void *sale_nod(void *arg)
{
    while(1){
        //sleep(1);
        //修改全局公共条件,用加锁保护
        pthread_mutex_lock(&mutex);
        if(basket == 0){
            printf("sale noddle!\n");
            basket = 1;
            //pthread_cond_broadcast();  唤醒所有等待在条件变量上的线程
            //pthread_cond_signal();   唤醒第一个等待在条件变量上的线程
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *buy_nod(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex); //加锁保护
        if(basket == 0){
            //条件变量和互斥锁搭配使用
            //wait是先对互斥锁判断是否加锁,如果加锁就解锁
            //然后陷入等待休眠-------------这是一个原子操作
            //防止情况: 没有资源但是消费者速度比较快先拿到锁,这样生产者拿不到锁没法生产
            //造成双方死锁
            //如果消费者先获取到锁,那么在陷入等待执前需要先解锁
            //这里的锁的存在是为了保护全局条件的操作是受保护的(basket)
            pthread_cond_wait(&cond, &mutex); //消费者先等待,等待生产者唤醒
        }
        else{
            printf("buy noddle!\n");
            basket = 0;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    pthread_cond_init(&cond, NULL); //条件变量初始化
    pthread_mutex_init(&mutex, NULL); //条件变量初始化
    int ret = pthread_create(&tid1, NULL, sale_nod, NULL);
    if(ret < 0){
        perror("pthread_create");
        return -1;
    }

    ret = pthread_create(&tid2, NULL, buy_nod, NULL);
    if(ret < 0){
        perror("pthread_create");
        return -1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
