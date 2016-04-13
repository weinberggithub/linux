#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include<sys/epoll.h>

typedef struct {
	pid_t pid;
	int fdw;
	int busy;
}child,*pchild;

typedef struct{
//	int flags;
	int len;
	char buf[1000];
}data;
typedef struct{
	int key;
	char *cm;
	char *argc;
}comm,*pcomm;

typedef struct node{
	struct node* pnext;
}node_t;
#define DOWNLOAD "hello.avi"

void child_handle(int);
void send_file(int);
int ls_func(int);
void cd_func();
void pwd_func();
void rm_func();
void gets_func();
void puts_func();
