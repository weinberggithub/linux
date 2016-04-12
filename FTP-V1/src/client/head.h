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

#define COM_ARGC_LEN 128

typedef struct {
	pid_t pid;
	int fdw;
	int busy;
}child,*pchild;

typedef struct{
	int flags;
	int len;//buf的实际发送长度
	char buf[1000];
}data;

typedef struct{
	int key;
	char comm_argc[COM_ARGC_LEN];
}comm,*pcomm;

typedef struct node{
	struct node* pnext;
}node_t;
#define DOWNLOAD "hello.avi"

void child_handle(int);
void send_file(int);
