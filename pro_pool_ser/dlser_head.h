#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<strings.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/wait.h>
typedef struct{
	int len;
	char buf[1000];
}data;

typedef struct{
	pid_t pid;
	int fdw;
	int busy;	
}child,*pchild;

#define DOWNLOAD "file"

void mkchild(pchild,int);
void child_handle(int);
void send_file(int);
int send_n(int,char*,int);
int recv_n(int,char*,int);
