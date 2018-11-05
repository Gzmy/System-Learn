#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *th_start(void *arg)
{
    sleep(3);
    pthread_exit("gzy");
    return "hello world!!";
}

int main()
{
    //线程等待  pthread_join
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, th_start, NULL);
    if(ret != 0){
        perror("pthread_create");
        return -1;
    }

    //如果调用join函数线程退出,那么直接返回,否则将陷入阻塞等待,知道指定线程退出
    
    pthread_cancel(tid);
    sleep(5);
    char *ptr;
    pthread_join(tid, (void**)&ptr);
    printf("child thread say:%d\n", (int)ptr);
    return 0;
}
