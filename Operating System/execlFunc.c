#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

int main(){

 printf("Before\n");
 
 execl("/bin/ls","ls","-l",NULL);
 //you can also write this:execl("/bin/ls","ls",NULL);
 //you can also write this:execl("/bin/ps","ps",NULL); 
 //any command
 
  printf("After\n");


}
