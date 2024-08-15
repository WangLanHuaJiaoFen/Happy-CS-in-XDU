#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

int main(){
    // int mkfifo(const char *filename,mode_t mode);
    int pipe_id_p = 0;
    int pipe_id_c = 0;
    const char* fifo_name = "/home/rongrong/os_exp/five/fifo.tmp";

    int res = 0;
    // 创建命名管道
    res = mkfifo(fifo_name, S_IFIFO);
   
    //创建子进程
    int proc_id = 0;
    while((proc_id = fork()) == -1);

    // 打开命名管道有4种方式
    // open(const char *path, O_RDONLY); // 1
    //open(const char *path, O_RDONLY | O_NONBLOCK); // 2
    //open(const char *path, O_WRONLY); // 3
    //open(const char *path, O_WRONLY | O_NONBLOCK); // 4
    if(proc_id == 0){
        // 子进程
        pipe_id_c = open(fifo_name, O_WRONLY);
        char st[] = "this is the content in the named pipe.";
        printf("child_p write to the named pipe: %s\n", st);
        if(pipe_id_c != -1){
            write(pipe_id_c, st, sizeof(st));
        } else {
            perror("open");
        }
        
        close(pipe_id_c);
    } else if(proc_id > 0){
        // 父进程
       
        pipe_id_p = open(fifo_name, O_RDONLY);
        char msg[50] = {0};
      
        if(pipe_id_p != -1){
            read(pipe_id_p, msg, sizeof(msg));
        }
        close(pipe_id_p);
        printf("parent_p read from the named pipe: %s\n", msg);
    }

    return 0;
}

