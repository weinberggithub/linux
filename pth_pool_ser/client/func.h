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
	int len;//代表后面buf的实际发送长度
	char buf[1000];
}data;


#define DOWNLOAD "hello.avi"
void make_child(pchild,int);//创建多个子进程用于给客户端发送文件
void child_handle(int);
void send_file(int);
