#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <errno.h>

#define SIZE 4096

int main()
{
    int fd,i,n=1;
    unsigned char buff[SIZE];
    fd = open("/dev/globalfifo", O_RDWR|O_NONBLOCK);
    if(fd < 0){
        printf("open error！ %s \n",strerror(errno));
        exit(1);
    }

//    write(fd,"xiao",5);
//    while(n!=0){
    n = read(fd, buff, SIZE);
//    printf("n = %d\n",n);
    write(1, buff, n);
//    buff[n]='\0';
//    printf("buff = %s\n",buff);
  //  }
    close(fd);
    return 0;
} 
