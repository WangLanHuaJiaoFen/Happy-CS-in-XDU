#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>


int main(){
    key_t key = ftok(".", 1);
    
    if(key == -1){
        perror("ftok");
        exit(1);
    }
    
    int shmid;
    shmid = shmget(key, 2*1024, IPC_CREAT|0666);
    if(shmid==-1){
        perror("shmget");
    }

    char* p = (char*)shmat(shmid, NULL, 0);
    char s[20] = {0};
    for(int i = 0; i < 8; i++){
        s[i] = *(p+i);
    }
    printf("reader gets from the writer: %s\n", s); 
    return 0;
}
