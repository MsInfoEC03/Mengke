#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static void sig_bye();
pid_t pid;
int cfd,addrlen=0,i=0,n=0,fd[2];
char buf[22],addr_str[20],name[11][20]; 

struct sockaddr_in si_recv;
struct sockaddr_in si;

int main(int argc,char** argv)
{
        if(pipe(fd)<0){
            printf("Pipe Error!");
        }
	if((pid = fork()) < 0)
		printf("fork error!");
	else if(pid > 0){

                close(fd[1]);

		cfd = socket(AF_INET,SOCK_DGRAM,0);
 
		int n = 1;  //  0表示关闭属性，非0表示打开属性  
		setsockopt(cfd, SOL_SOCKET, SO_BROADCAST, &n, sizeof(n));//广播设置  
   
		si.sin_family = AF_INET;
		si.sin_port = htons(6666);
		si.sin_addr.s_addr = inet_addr("255.255.255.255");  //这是对局域网全网段  
  
		char buf[22];
		if(signal(SIGINT,sig_bye) == SIG_ERR)
			printf("can't catch signalbye!");
 
		sendto(cfd,"online:mengke",23,0,(struct sockaddr *)&si,sizeof(si));
		//si.sin_addr.s_addr = inet_addr((char *)argv[1]);
		while(1)
		{
			bzero(buf,22);
		//	printf("Input:");
			scanf("%s",buf);

		    if(buf[0] == ':'){
                       if( strcmp(buf,":all") == 0)
		           si.sin_addr.s_addr = inet_addr("255.255.255.255");  //这是对局域网全网段
		       else if(strncmp(buf, ":192.168.0.", 11) == 0)
		           si.sin_addr.s_addr = inet_addr((buf+1));  //这是对局域网全网段
                       else if( strcmp(buf,":ls") == 0){
                            while(1){
			        n = read(fd[0],name[i],12);
                                if(n == 0) {i=0; break;}
                                write(STDOUT_FILENO,name[i],n);
			    }
                       }
                    }        
		    else{
			sendto(cfd,buf,22,0,(struct sockaddr *)&si,sizeof(si));
		    }
		}
		close(cfd);
		return 0;
	}
//接受 服务器端
	else
	{
		close(fd[0]);
		
		cfd = socket(AF_INET, SOCK_DGRAM, 0);
		if(cfd < 0)
		{
			printf("socket error!\n");
			return 0;
		}

    
		addrlen = sizeof(si);
		bzero(&si,addrlen);
		si.sin_family = AF_INET;
		si.sin_port = htons(6666);
		si.sin_addr.s_addr = INADDR_ANY;
      
		//绑定  
		int ret = bind(cfd, (struct sockaddr *)&si, sizeof(si));
		if(ret == -1)
		{  
			printf("bind error!\n");
			return 0;
		}   
  
		addrlen = sizeof(si_recv);
		bzero(&si_recv,addrlen);
		si_recv.sin_family = AF_INET;
		si_recv.sin_port = htons(6666);
		si_recv.sin_addr.s_addr = INADDR_ANY;
		while(1)
		{
			bzero(buf,22);
			recvfrom(cfd, buf, 21, 0, (struct sockaddr*)&si_recv, &addrlen);
                        if( strncmp(buf,"online:",7) == 0){
			    memmove(name[i], buf, 22);
                            write(fd[1],name[i],22);
                            i++;
                            if(i>=10) i=0;
		        } 
                        else{
			    inet_ntop( AF_INET , &si_recv.sin_addr , addr_str ,20);
			    printf("%s: %s\n" , addr_str , buf);
                        }
		}

		close(cfd);
		return 0;
	}
}

static void sig_bye()
{
    si.sin_addr.s_addr = inet_addr("255.255.255.255");  //这是对局域网全网段
    sendto(cfd,"offline:mengke!",15,0,(struct sockaddr *)&si,sizeof(si));
    exit(0);
}


