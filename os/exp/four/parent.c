#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int p_to_c[2];

int main(){
    // 创建匿名管道
    pipe(p_to_c);
    
    int proc_id = 0;
    // 创建子进程
    while((proc_id=fork()) == -1);
    if(proc_id == 0) {
        // 子进程
        waitpid(getppid(), NULL, 0);

        char content[50];
        // close write
        close(p_to_c[1]);
        read(p_to_c[0], content, sizeof(content));
        printf("child gets from parent %s\n", content);
        close(p_to_c[0]);
        exit(1);
    }else if(proc_id > 0) {
        // 父进程
        char msg[] = "Hello, this is the specific content.";
        // 关闭读端
        close(p_to_c[0]);
        // 从写端写入
        write(p_to_c[1], msg, sizeof(msg));
        printf("parent's content: %s\n",msg); 
        // 关闭写端
        close(p_to_c[1]);
    }
    return 0;
}
