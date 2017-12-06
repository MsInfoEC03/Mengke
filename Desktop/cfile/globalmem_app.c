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
    int fd,i,n;
    unsigned char *mmap_addr;
    unsigned int buff[SIZE];
//    unsigned int dat[10]={10,11,12,13,14,15,16,17,18,19};
    fd = open("/dev/globalmem", O_RDWR);
    if(fd < 0){
        printf("open error！ %s \n",strerror(errno));
        exit(1);
    }

    mmap_addr = (unsigned char *)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(mmap_addr == MAP_FAILED){
        printf("mmap error!\n");
    }
    
    for(i = 0;i < 10;i++)
    {
        mmap_addr[i] = 'b'+i;
        printf("mmap = %c\n",mmap_addr[i]);
      //  printf("%d\n",mmap_addr);
    }
//    n =  write(fd,"hello\n", 6);    
//    read(fd, buff, SIZE);
//    for(i=0;i<100;i++)
 //       printf("buff = %d\n",buff[i]);
    munmap(mmap_addr, SIZE);
    close(fd);
    return 0;
} 
