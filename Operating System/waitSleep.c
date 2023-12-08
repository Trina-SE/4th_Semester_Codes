#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<stdio.h>

int main(){

 pid_t f;
 
 f=fork();
 
 if(f<0){
 
   printf("No child process is created\n");
 
 }
 
 else if(f==0){
     
     printf("Child process is running\n");
     //sleep(3);
     printf("Child having pid_: %d\n",getpid());//getpid()->current process er id print kore->ja child
     printf("Parent having pid_: %d\n",getppid()); //getppid()->parent id
     printf("Hello\n");
 }
 else if(f>0){
 
    wait(NULL); //wait cannot be used in child process. "wait" tar child er jonno wait kore ejonno
 
     printf("Parent Process is Running\n");
     
     //sleep(3);
     
     printf("Parent having pid: %d\n",getpid());//current process er id print korlo->ja parent
     printf("Child having pid: %d\n",f); //here current process is parent, so getppid will not work for finding child id. Here "f" contains this id;
     printf("TRINA\n");
 }
 
 printf("Parent & Child both will execute this portion\n");

}

