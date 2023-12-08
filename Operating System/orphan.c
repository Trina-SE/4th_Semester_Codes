#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

int main(){

 pid_t p;
 p=fork();
 
 if(p==0){
   sleep(2);
   printf("I'm child process having pid:%d\n",getpid());
   printf("My parent is:%d\n",getppid());
 
 }
 
 else{
 
   printf("I'm parent process having pid:%d\n",getpid());
   printf("My child is:%d\n",p);
 
 }


}
