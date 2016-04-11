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

typedef struct {
	pid_t pid;
	int fdw;
	int busy;
}child,*pchild;

typedef struct{
	int len;//buf的实际发送长度
	char buf[1000];
}data;

typedef struct{
	char comm_name;
	int key;
	char comm_argc;
}comm;*pcomm;

typedef struct node{
	pnode head,tail;
	struct node* pnext;
}node_t,*pnode;
#define DOWNLOAD "hello.avi"

void child_handle(int);
void send_file(int);
