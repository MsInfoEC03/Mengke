#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int i=2;
void* th_fun(void *arg)
{
while(1){
    printf("111111111111111111111111\n");
//    if(i>=10) pthread_exit((void *)2);

}
}

int main()
{
    pthread_t tid;
    pid_t pid;
    int n,err;
    
    pthread_mutex_t lock;
    if((n = pthread_mutex_init(&lock , NULL)) != 0)
        printf("initlock error:%d\n",n);
    if((err = pthread_create(&tid , NULL , th_fun , NULL)) != 0)
        printf("create error:%d\n",err);
    
    while(1){
        printf("%d\n",i);
        i++;
        
    if(i>=10) pthread_exit((void *)2);
    }
    

    

}



