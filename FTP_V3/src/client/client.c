#include "head.h"

int ls_func(int sfd)
{
	int ret;
	int len; 
	char buf[1024] = {0};
	while(1)
	{
		printf("hello,before recv_n\n");
		ret = recv_n(sfd,&len,sizeof(int));
		if(ret == -1)
		{
			perror("recv1");
			return -1;
		}
//		printf("%d\n",len);
		if(len == 0)
		{
			break;
		}
		bzero(buf,sizeof(buf));
		ret = recv_n(sfd,buf,len);
		if(ret == -1)
		{
			perror("recv2");
			return -1;
		}
		printf("%s",buf);
	}
	return 0;
}
int cd_func(int sfd){
	int len;
	int ret;
	char buf[1024] = {0};
	bzero(buf,sizeof(buf));
	ret = recv_n(sfd,&len,sizeof(int));
	if(ret == -1)
	{
		perror("recv1");
		return -1;
	}
	
}
int pwd_func(int sfd){
	int len;
	int ret;
	char buf[1024] = {0};
	bzero(buf,sizeof(buf));
	ret = recv_n(sfd,buf,sizeof(buf));
	if(ret == -1)
	{
		perror("recv1");
	}
	printf("%s",buf);
}
int rm_func(int sfd){
	int ret;
	char buf[1024] = {0};
	ret = recv_n(sfd,buf);
	if(ret == -1)
	{
		perror("recv");
		return -1;
	}
	printf("%s",buf);
}
int gets_func(int sfd){
	int len;
	int ret;
	char buf[1024] = {0};
	ret = recv_n(sfd,(char*)&len,sizeof(int));
	if(ret == -1)
	{
		perror("recv1");
		return -1;
	}
	ret = recv_n(sfd,buf,sizeof(buf));
	if(ret == -1)
	{
		perror("recv2");
	}
	int fd = open(buf,O_CREAT|O_RDWR,0666);
	if(-1 == fd)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		ret = recv_n(sfd,&len,sizeof(int));
		if(ret == -1)
		{
			perror("recv3");
			return -1;
		}
		if(len == 0)
		{
			break;
		}
		bzero(buf,sizeof(buf));
		ret = recv_n(sfd,buf,len);
		if(ret == -1)
		{
			perror("recv4");
			return -1;
		}
		ret = write(fd,buf,len);
		if(ret == -1)
		{
			perror("write");
			return -1;
		}
	}
	close(fd);
	close(sfd);
}
int puts_func(int sfd){
	
}
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
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
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
	pcomm pc;
	data d;
	pc = (pcomm)malloc(sizeof(comm));
	bzero(&d,sizeof(d));
	bzero(pc,sizeof(comm));
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
					ret1 = read(0,buf,sizeof(buf));
					if(ret1 == -1)
					{
						perror("read");	
						return -1;
					}
					ret1 = comm_analyze(buf,pc);
					if(ret1 == -1)
					{
						printf("invalid comm\n");
						return -1;
					}
					d.len = sizeof(comm);
					ret1 = send(sfd,(int*)&d.len,sizeof(int),0);
					if(ret1 == -1)
					{
						perror("send1");
						return -1;
					}
					ret1 = send(sfd,pc,sizeof(comm),0);
					if(ret1 == -1)
					{
						perror("send2");
						return -1;
					}
				} 
//				printf("%d\n",comm->key);
				if(evs[i].events == EPOLLIN || evs[i].data.fd == sfd)
				{
					switch(pc->key)
					{
						case 1:ret1 = ls_func(sfd);printf("%d\n",ret1);break;
						case 2:cd_func(sfd);break;
						case 3:pwd_func(sfd);break;
						case 4:rm_func(sfd);break;
						case 5:puts_func(sfd);break;
						case 6:gets_func(sfd);break;
					}
				}
			}
		}
	}
	close(sfd);
}
