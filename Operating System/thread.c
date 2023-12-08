#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<pthread.h>

void *work_thread(void * arg);

int main(){

 pthread_t thread;
 
 pthread_create(&thread, NULL, work_thread, NULL);
 //pthread_create(&thread er num, NULL, thread ta ki kaj korbe oitar function , function er moddhe kisu pass korale);
 
 pthread_join(thread,NULL); //process wait for thread to finish
 //pthread_join(thread er num,thread ja return korbe seta jekhane store hobe);
 
 printf("Inside main\n");
 
 for(int i=0;i<7;i++){
 
 printf("%d ",i);
 
 }

}

void *work_thread(void * arg){
   printf("Inside func\n");
 
 for(int i=0;i<4;i++){
 
 printf("func\t");
 
 }
 printf("\n");
}

//when compile, gcc name.c -lpthread
