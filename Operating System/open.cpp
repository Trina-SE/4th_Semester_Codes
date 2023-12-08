#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>

int main(){

  int file,file1,n;
  
  char buf[300];
  
  file=open("text.txt",O_RDONLY);

  n=read(file,buf,300);
  
  printf("%s",buf); //print file in screen
  
  file1=open("writeText.txt",O_CREAT|O_WRONLY,0642); //print file in another file
//  file1=open("writeText.txt",O_CREAT|O_WRONLY,0642); //print file in another file
  
  write(file1,buf,n);

}
