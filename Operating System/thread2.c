#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<pthread.h>

void *work_thread(void * arg);

int main(){

 pthread_t thread;
 
 void *msg;
 
 char *character="Trina";
 
 pthread_create(&thread, NULL, work_thread,character);
 
 pthread_join(thread, &msg); //process wait for thread to finish
 
 printf("Inside main\n");
 
 printf("Thread returned:%s",(char*)msg);
 

}

void *work_thread(void * arg){

   printf("Inside func\n");
 
   char *x=arg;
 
   printf("%s\n",x);
 
   pthread_exit("Returned a MESSAGE\n");
}

//when compile, gcc name.c -lpthread
