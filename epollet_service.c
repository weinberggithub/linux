#include "head1.h"
void set_nonblock(int *fd)
{
	int status;
	status = fcntl(*fd,F_GETFL);
	status = status | O_NONBLOCK;
	fcntl(*fd,F_SETFL,status);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("args error\n");
		return -1;
	}
	int sfd;
	int ret;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	ret = bind(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("bind");
		exit(-1);
	}
	ret = listen(sfd,LNUM);
	if(ret == -1)
	{
		perror("listen");
		exit(-1);
	}
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen;
	addrlen = sizeof(struct sockaddr);
	int newfd = -1;
//	fd_set rdset;
//	fd_set newset;
//	int maxfd;
//	FD_ZERO(&newset);
	int epfd = epoll_create(1);
	if(-1 == epfd)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event,evs[3];
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
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	char buf[10] = {0};
	int i;
	int ret1;
	while(1)
	{
//		FD_ZERO(&rdset);
//		FD_SET(0,&newset);
//		FD_SET(sfd,&newset);
//		memcpy(&rdset,&newset,sizeof(rdset));
//		if(FD_ISSET(newfd,&newset))
//		{
//			maxfd = newfd + 1;
//		}else{
//			maxfd = sfd + 1;
//		}
//		ret = select(maxfd,&rdset,NULL,NULL,NULL);
		bzero(evs,sizeof(evs));
		
		ret1 = epoll_wait(epfd,evs,3,-1);
//		if(ret > 0)
		for(i = 0;i < ret1;i++)
		{
//			if(FD_ISSET(sfd,&rdset))
			if(evs[i].events == EPOLLIN && evs[i].data.fd == sfd)
			{
				newfd = accept(sfd,(struct sockaddr*)&client,&addrlen);
				if(newfd == -1)
				{
					perror("accept");
					exit(-1);
				}
				printf("client ip=%s port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
//				FD_SET(newfd,&newset);
				event.events = EPOLLIN | EPOLLET;
				event.data.fd = newfd;
				set_nonblock(&newfd);
				epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&event);
			}
//			if(FD_ISSET(newfd,&rdset))
			if(evs[i].events == EPOLLIN && evs[i].data.fd == newfd)
			{
				while(1)
				{
					bzero(buf,sizeof(buf));
					ret = recv(newfd,buf,sizeof(buf),0);
					if(ret < 0)
					{
//						perror("recv");
//						exit(-1);
						break;
					}else if(ret == 0)
					{
						close(newfd);
//						FD_CLR(newfd,&newset);
						event.data.fd = newfd;
						epoll_ctl(epfd,EPOLL_CTL_DEL,newfd,&event);
					}else if(ret > 0){
						printf("%s\n",buf);
					}
				}
			}
//		}
//		if(FD_ISSET(0,&rdset))
			if(evs[i].events == EPOLLIN && evs[i].data.fd == 0)
			{	
				bzero(buf,sizeof(buf));
				read(0,buf,sizeof(buf));
				ret = send(newfd,buf,strlen(buf) - 1,0);
//				printf("%d\n",ret);
//				printf("%s\n",buf);
				if(ret == -1)
				{
					perror("sened");
					exit(-1);
				}
			}
		}
	}
	close(sfd);
	return 0;
}
