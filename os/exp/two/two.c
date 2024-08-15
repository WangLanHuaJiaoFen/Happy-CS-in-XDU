#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int globalData = 0;
int* globalPointer = NULL;

void* thread1(void* arg){
    // 用于修改进程数据
    printf("before fix: %d\n", globalData);
    globalData = 100;
    printf("after fix: %d\n", globalData);
   
    // 用于修改线程数据
    globalPointer = (int*)malloc(sizeof(int));
    *globalPointer = 10;
    return NULL;
}

void* thread2(void* arg){
    printf("before: %d\n", *globalPointer);
    *globalPointer = 204;
    printf("after: %d\n", *globalPointer);
    return NULL;
}

int main(){
    pthread_t threadId1, threadId2;
    int err = pthread_create(&threadId1, NULL, thread1, NULL);
   
    //int pthread_create(pthread_t *tid, const pthread_arrt_t* attr,
    //void*(*start_routine)(void *), void* arg);
    
    //int pthread_join(pthread_t thread, void **retval);//等待线程结束

    pthread_join(threadId1, NULL);
    err = pthread_create(&threadId2, NULL, thread2, NULL);
    pthread_join(threadId2, NULL);
    return 0;
}

