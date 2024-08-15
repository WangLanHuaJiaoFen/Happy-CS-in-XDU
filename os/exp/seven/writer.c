#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/ipc.h>
int main(){
    // key_t ftok(const char *pathname, int proj_id);
    // 用于生成基于给定路径和项目ID关联的唯一ID值
    // 根据路径和标识符proj_id生成key值用于共享内存
    key_t key = ftok(".", 1);
    
    if(key == -1) {
        perror("ftok");
        exit(1);
    }
    
    //int shmget(key_t  key, size_t  size, int shmflg)得到一个共享内存标识符或创建一个共享内存对象,共享内存标识符key通常要求此值来源于ftok返回的IPC键值.
    //size新建的共享内存大小，以字节为单位.
    //shmflg标志位，用于指定共享内存的权限和行为，若不存在则函数会报错
    //IPC_CREAT若不存在创建新的
    
    //建立共享内存区
    int shmid;
    // 得到共享内存标识符
    shmid = shmget(key, 2*1024, IPC_CREAT|0666);
    if(shmid == -1){
        perror("shmget");
    }

    //void *shmat(int shmid, const void *shmaddr, int shmflg)连接共享内存标识符为shmid的共享内存，连接成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问.
    //shmid共享内存标识符
    //shmaddr指定共享内存出现在进程内存地址的什么位置，直接指定为NULL让内核自己决定一个合适的地址位置
    //Shmflg    规定主存的读写权限
    char s[20] = "wbb wudi";
    char* p = (char*)shmat(shmid, NULL, 0);
    for(int i = 0; i < strlen(s); i++){
        *(p+i) = s[i];
    }
    printf("writer writes: %s\n", s);
    //int shmdt(char*addr) 把共享主存从指定进程的虚拟地址空间断开。
    //addr是要断开连接的虚拟地址 
   
    // 连接拆除
    int dt = shmdt(p);
    if(dt == -1){
        perror("shmdt");
    }
    return 0;

}
