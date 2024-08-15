#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    int proc_id = 0;
    while((proc_id=fork()) == -1);

    if(proc_id>0){
        // 父
        printf("start waiting\n");
        proc_id = waitpid(proc_id, NULL, 0); // 等待子进程结束
        printf("parent_proc wait over\n");
        // prc
    } else {
        for(int i = 0; i < 100; i++){
            FILE* f = fopen("./content.txt", "r");
       }
        printf("child_proc read over\n");
    }
    return 0;
}

