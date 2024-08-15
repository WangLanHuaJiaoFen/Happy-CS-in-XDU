#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    // O_CREAT|O_RDWR 没有就创建，有就打开
    // 0666访问权限
    // 5,0初始值
    sem_t* p = sem_open("/S1", O_CREAT|O_RDWR, 0666, 5);
    sem_t* s = sem_open("/S2", O_CREAT|O_RDWR, 0666, 0);
    sem_t* mutex = sem_open("/mutex",  O_CREAT|O_RDWR, 0666, 1);
    if(p == SEM_FAILED || s == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    // 信号量初值
    sem_init(p, 1, 5);
    sem_init(s, 1, 0);
    sem_init(mutex, 1, 1);

    int proc_id = 0;
    // 创建三个子进程作为消费者
    while((proc_id = fork()) == -1);
    while((proc_id = fork()) == -1);
    while((proc_id = fork()) == -1);

    int* current = NULL;
    int* current_p = NULL;
    if(proc_id == 0) {
        // 消费者
        while(1){
            sleep(1);
            sem_wait(s);//P
            sem_wait(mutex);//P
            printf("拿出一件产品\n");
            sem_post(mutex);//V
            sem_post(p);//V
            printf("消费产品\n");
            printf("out consumer, into producer\n\n");

        }
    } else if(proc_id > 0){
        // 生产者
        while(1){
            sem_wait(p);//P
            sem_wait(mutex);//P
            printf("放入一件产品\n");
            sem_post(mutex);//V
            sem_post(s);//V
            printf("out producer, into consumer\n\n");
            sleep(0.5);
        }
    }


    return 0;
}

