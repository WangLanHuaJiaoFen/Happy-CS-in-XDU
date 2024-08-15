#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

// <signal.h>
// sighandler_t signal(int signum,sighandler_t handler);
// 设置某一个信号对应的动作
// param1 signum:信号类型
// param2 handler 相关动作
// ret 先前的信号函数处理指针，若错误返回SIG_ERR（-1）要求只有一个int参数,无ret
//
// <signal.h>
// <sys/types.h>
// int kill(pid_t pid,int signo);
// 发送信号
// param1 发送对象进程的pid
// signo 发送信号值

void sigchld_handler(int sig) {
    printf("this is the named event created by parent proc.\n");
    printf("recieving the signal.\n");
}

void bro_sigchld_handler(int sig) {
    printf("this is signal passing in bro to bro.\n");
}

int main() {
    int child_id1 = 0;
    int child_id2 = 0;
    // map信号和事件
    signal(SIGUSR2, sigchld_handler);
    // 创建子进程1
    while((child_id1 = fork()) == -1);
    if(child_id1 == 0 && child_id2 == 0) {
        // 第一个子进程序
        signal(SIGUSR1, bro_sigchld_handler);
    }

    if(child_id1 > 0) {
        // 创建子进程的兄弟进程
        while((child_id2 = fork()) == -1);
    }
    // parent_proc: child_id1 = pid1 child_id2 = pid2
    // child_proc1: child_id1 = 0 child_id2 = 0
    // child_proc2: child_id1 = pid1 child_id2 = 0

    if(child_id1 > 0 && child_id2 > 0) {
        // 父进程等待所有子进程执行
        waitpid(child_id1, NULL, 0);
        waitpid(child_id2, NULL, 0);
    }
  
    if(child_id1 > 0 && child_id2 == 0){
        // 第二个子进程
        printf("this is child proc2\n");
        // 向第一个子进程发送信号
        kill(child_id1, SIGUSR1);
        sleep(1);
        exit(1);
    } else if(child_id1 == 0 && child_id2 == 0) {
        // 保证第二个子进程先执行
        sleep(2);
        // 第一个子进程
        printf("this is child proc1\n");
        // 向父进程发送信号
        kill(getppid(), SIGUSR2);
        sleep(1);
        exit(1);
    } else if(child_id1 > 0 && child_id2 > 0) {
        printf("this is parent proc\n");
        exit(1);
    }
    return 0;

}

