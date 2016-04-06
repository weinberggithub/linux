#include "head1.h"

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("args error\n");
		return -1;
	}
	int ret;
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	ret = connect(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	printf("here\n");
	if(ret == -1)
	{
		perror("connect");
		return -1;
	}
	char buf[128] = {0};
//	fd_set rdset;
	int epfd = epoll_create(1);
	if(epfd == -1)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event,evs[2];
	event.events = EPOLLIN;
	event.data.fd = 0;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	event.events = EPOLLIN;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	int i;
	int ret1;
	while(1)
	{
//		FD_ZERO(&rdset);
//		FD_SET(0,&rdset);
//		FD_SET(sfd,&rdset);
//		ret = select(sfd + 1,&rdset,NULL,NULL,NULL);
		bzero(evs,sizeof(evs));
		ret1 = epoll_wait(epfd,evs,2,-1);
//		if(ret > 0)
		for(i = 0;i < ret1;i++)
		{
//			if(FD_ISSET(0,&rdset))
			if(evs[i].events == EPOLLIN && evs[i].data.fd == 0)
			{
				bzero(buf,sizeof(buf));
				ret = read(0,buf,sizeof(buf));
				if(ret == -1)
				{
					perror("read");
					return -1;
				}
				ret = send(sfd,buf,strlen(buf) - 1,0);
				if(ret == -1)
				{
					perror("send");
					return -1;
				}
			}
//			if(FD_ISSET(sfd,&rdset))
			if(evs[i].events == EPOLLIN && evs[i].data.fd == sfd)
			{
				bzero(buf,sizeof(buf));
				ret = recv(sfd,buf,sizeof(buf),0);
				if(ret == -1)
				{
					perror("recv");
					return -1;
				}
				printf("%s\n",buf);
			}
		}
	}
	close(sfd);
	return 0;
}

