#include "head.h"

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
//	comm_ctl_init();
	int epfd = epoll_create(1);
	if(epfd == -1)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event,evs[2];
	event.events = EPOLLIN;
	event.data.fd = 0;
	ret == epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	event.events = EPOLLIN;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	char buf[1024] = {0};
	int i;
	int ret1;
	data comm_d;
	bzero(&comm_d,sizeof(comm_d));
	while(1)
	{
		bzero(buf,sizeof(buf));
		ret = epoll_wait(epfd,evs,2,-1);
		if(ret > 0)
		{
			for(i = 0;i < ret;i++)
			{
				bzero(buf,sizeof(buf));
				if(evs[i].events == EPOLLIN && evs[i].data.fd == 0)
				{
					while(1)
					{
						ret1 = read(0,buf,sizeof(buf));
						if(ret1 == -1)
						{
							perror("read");	
							return -1;
						}
						ret1 = comm_analyze(buf,&comm_d);//该函数解析输入流中读到的命令，不存在此命令返回-1，存在则返回相应命令的key值。
//						printf("%d\n",ret1);
						if(ret1 == -1)
						{
							printf("invalid comm\n");
							return -1;
						}
						ret1 = send(sfd,&comm_d,sizeof(comm_d),0);
						if(ret1 == -1)
						{
							perror("send");
							return -1;
						}
						while(bzero(&buf,sizeof(buf)),(ret1 = recv(sfd,buf,sizeof(buf),0)) > 0)
						{
							printf("%s",buf);
						}
					}
				}
			}
		}
	}
//	char buf[1024]={0};
//	int len;
//	ret=recv_n(sfd,(char*)&len,sizeof(int));
//	if(-1==ret)
//	{
//		perror("recv");
//		exit(-1);
//	}
//	ret=recv(sfd,buf,len,0);
//	if(-1==ret)
//	{
//		perror("recv");
//		exit(-1);
//	}
//	int fd;
//	fd=open(buf,O_CREAT|O_RDWR,0666);
//	if(-1==fd)
//	{
//		perror("open");
//		return -1;
//	}
//	while(1)
//	{
//		//客户端在连接上之后，读取IO输入，先发送命令给服务器，同时记录命令
//		//send()
//		ret=recv_n(sfd,&len,sizeof(int));
//		if(-1==ret)
//		{
//			perror("recv1");
//			exit(-1);
//		}
//		if(len==0)
//		{
//			break;
//		}
//		bzero(buf,sizeof(buf));
//		ret=recv_n(sfd,buf,len);
//		if(-1==ret)
//		{
//			perror("recv2");
//			exit(-1);
//		}
//		ret=write(fd,buf,len);
//		if(-1==ret)
//		{
//			perror("write");
//			return -1;
//		}
//	}
//	close(fd);
	close(sfd);
}
