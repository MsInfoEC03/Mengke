#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

pid_t pid;
int fd[2],fd1[2];
int n,n1;
char line[20],line1[20];

int main()
{
    if(pipe(fd)<0){
        printf("Pipe Error!");
    }
    if(pipe(fd1)<0){
        printf("Pipe1 Error!");
    }
    if((pid=fork())<0){
        printf("Fork Error!");
    }
    else if(pid==0){
        close(fd[1]);
        close(fd1[0]);
        write(fd1[1],"\nMe too!\n",12);
        n = read(fd[0],line,12);
        write(STDOUT_FILENO,line,n);
    } 
    else{
        close(fd[0]);
        close(fd1[1]);
        write(fd[1],"\nI love you!\n",12);
        n1 = read(fd1[0],line1,12);
        wait(NULL);
        write(STDOUT_FILENO,line1,n1);
    }
return 0; 
}
