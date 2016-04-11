#include "func.h"

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));//端口转换为网络字节序
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	char buf[1024]={0};
	int len;
	ret=recv_n(sfd,(char*)&len,sizeof(int));
	if(-1==ret)
	{
		perror("recv");
		exit(-1);
	}
	ret=recv(sfd,buf,len,0);
	if(-1==ret)
	{
		perror("recv");
		exit(-1);
	}
	int fd;
	fd=open(buf,O_CREAT|O_RDWR,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		//客户端在连接上之后，读取IO输入，先发送命令给服务器，同时记录命令
		//send()
		ret=recv_n(sfd,&len,sizeof(int));
		if(-1==ret)
		{
			perror("recv1");
			exit(-1);
		}
		if(len==0)
		{
			break;
		}
		bzero(buf,sizeof(buf));
		ret=recv_n(sfd,buf,len);
		if(-1==ret)
		{
			perror("recv2");
			exit(-1);
		}
		ret=write(fd,buf,len);
		if(-1==ret)
		{
			perror("write");
			return -1;
		}
	}
	close(fd);
	close(sfd);
}
