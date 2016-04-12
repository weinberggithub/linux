#ifndef __HEAD_H__
#define __HEAD_H__
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
#include<pthread.h>
#include<dirent.h>

typedef struct
{
	int flags;
	int len;
	char buf[1000];
}data;

void send_file(int);
int send_n(int,char*,int);

#define DOWNLOAD "file"
#endif
