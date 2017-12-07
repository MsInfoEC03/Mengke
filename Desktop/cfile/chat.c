#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>


#define SIZEMAX 4096 

int f_pid1=3,f_pid2=3,n,flag_chat=0;
pid_t pid;
char line[SIZEMAX];

void chat_re();		//接受
void chat_se();		//发送

static void sig_bye();
static void sig_pipe();

int main(int argc,char* argv[])
{
 //   mkfifo("fifo_chat1",0777);
 //   mkfifo("fifo_chat2",0777);
if(signal(SIGINT,sig_bye) == SIG_ERR)
    printf("can't catch signalbye!");
if(signal(SIGPIPE,sig_pipe) == SIG_ERR)
    printf("can't catch signalpipe!");

printf("编译时间：%s ",__TIME__);
printf("本地时间：%s\n",__DATE__);

if(argv[1][0]=='1'){
    flag_chat = 1;
    printf("-- Welcome back 1 --\n");
}
if(argv[1][0]=='2'){
    flag_chat = 2;
    printf("-- Welcome back 2 --\n");
}

if(argc != 2){
    printf("agrv error!\n");
}
else{
    if((pid=fork())<0)
        printf("fork error!\n");
    else if(pid == 0){
        chat_se();
    }
    else{
        chat_re();
    }
}

return 0;
}

void chat_re()		//接受
{
//    printf("-- chat_re1 --\n");
    if(flag_chat == 1)
        f_pid1=open("fifo_chat1",O_RDONLY);
    else if(flag_chat == 2)
        f_pid1=open("fifo_chat2",O_RDONLY);
    if(f_pid1<0)
          printf("openfifo error!\n");
    else{
        while(1){ 
            n=read(f_pid1,line,SIZEMAX);
            if(n != 0){
                write(STDOUT_FILENO,"He: ",4);
                write(STDOUT_FILENO,line,n);
            }
        }
    }
}

void chat_se()		//发送
{
//    printf("-- chat_se1 --\n");
    if(flag_chat == 1)
        f_pid2=open("fifo_chat2",O_WRONLY);
    else if(flag_chat == 2)
        f_pid2=open("fifo_chat1",O_WRONLY);
    if(f_pid2<0){
        printf("Openfifo eror!\n");
    }
    else{
        while(1){
            n=read(STDIN_FILENO,line,SIZEMAX);
            write(f_pid2,line,n);
            write(STDOUT_FILENO,"Me: ",4);
            write(STDOUT_FILENO,line,n);
        }
    }
}

static void sig_bye()
{
    write(f_pid2,"Bye!\n",5);
    close(f_pid2);
    close(f_pid1);
    exit(0);
    
}
static void sig_pipe()
{
    write(STDOUT_FILENO,"---OUTLINE!---\n",15);
}
