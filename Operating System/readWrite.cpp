#include<unistd.h>

int main(){

  write(1,"Write your name:\n", 16);
  
  char name[100];
  int siz;
  siz=read(0,name,100);
  write(1,name,siz);

}
