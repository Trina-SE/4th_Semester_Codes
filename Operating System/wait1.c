#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<stdio.h>

int main(){

 pid_t f,f2;
 
 f=fork();
 
 if(f<0){
 
   printf("No child process is created\n");
 
 }
 
 else if(f==0){

  
     printf("Child-1 process is running\n");
     printf("Child-1 having pid: %d\n",getpid());
     printf("Parent of child-1 having pid: %d\n",getppid()); 
   
   }
  
 else if(f>0){
    
    f2=fork();
    
    if(f2<0) printf("error--2\n");
    else if(f2==0){
   
        printf("Child-2 process is running\n");
        printf("Child-2 having pid_: %d\n",getpid());
        printf("Parent of child-2 having pid_: %d\n",getppid());
   
   }
   else{
   
    waitpid(f2,NULL,0);//f2 age execute hobe
    
    //BUT it is not running correctly. why??????????????
   
     printf("Parent Process is Running\n");
     
     printf("Parent having pid: %d\n",getpid());
     printf("Child-1 having pid: %d\n",f); 
   }

 }
 
 printf("Parent & Child both will execute this portion\n");

}

