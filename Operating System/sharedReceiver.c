#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>

int main(){

 void *sharedmem;
 char buff[100];
 int shmid;
 
 shmid=shmget((key_t)1122,1024,0666);
 printf("Key of shared memory is:%d\n",shmid);
 sharedmem=shmat(shmid,NULL,0);
 printf("Process attached at :%p\n",sharedmem);
 //printf("Enter data to write into the shared memory:");
 read(0,buff,100);
 strcpy(sharedmem,buff);
 
 printf("Data read from shared memory:%s\n",(char*)sharedmem);
 

}
