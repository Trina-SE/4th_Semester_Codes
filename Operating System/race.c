#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include<pthread.h>

void *func1();
void *func2();

int shared=1;

int main(){

pthread_t thread1,thread2;

pthread_create(&thread1,NULL,func1,NULL);
pthread_create(&thread2,NULL,func2,NULL);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
printf("Shared value in main func is:%d\n",shared);

}

void *func1(){

  int x=shared;
  printf("Thread 1 is running\n");
  x++;
  printf("Local Update-1\n");
  sleep(1);
  shared=x;
  printf("Shared value in thread 1 is:%d\n",shared);
  
}

void *func2(){

  int y=shared;
  printf("Thread 2 is running\n");
  y--;
  printf("Local Update-2\n");
  sleep(1);
  shared=y;
  printf("Shared value in thread 2 is:%d\n",shared);
  


}

