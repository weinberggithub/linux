#include "dlser_head.h"

int main(int argc,char* argv[])
{
	if(argc != 4)
	{
		printf("args error\n");
		return -1;
	}
	int num = atoi(argv[3]);
	pchild p = (pchild)malloc(num*sizeof(child));
	mkchild(p,num);
	int sfd;
	sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		return -1;
	}
	int ret;
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[2]));
	ser.sin_addr.s_addr = inet_addr(argv[1]);
	ret = bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,num);
	int epfd = epoll_create(1);
	if(epfd == -1)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event,*evs;
	evs = (struct epoll_event*)malloc((num + 1)*sizeof(struct epoll_event));
	event.events = EPOLLIN;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	int i;
	for(i = 0;i < num;i++)
	{
		event.events = EPOLLIN;
		event.data.fd = p[i].fdw;
		ret = epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].fdw,&event);
		if(ret == -1)
		{
			perror("epoll_ctl");
			return -1;
		}
	}
	int newfd;
	int j;
	int flag;
	while(1)
	{
		bzero(&evs,sizeof(evs));
		ret = epoll_wait(epfd,evs,num + 1,-1);
		if(ret > 0)
		{
			for(i = 0;i < ret;i++)
			{
				if(evs[i].events == EPOLLIN && evs[i].data.fd == sfd)
				{
					newfd = accept(sfd,NULL,NULL);
					if(newfd == -1)
					{
						perror("accept");
						return -1;
					}
					for(j = 0;j < num;i++)
					{
						if(p[i].busy == 0)
						{
							break;
						}
					}
					if(j == num)
					{
						continue;
					}
					send_fd(p[j].fdw,newfd);
					p[j].busy = 1;
				}
				for(i = 0;i < num;i++)
				{
					if(evs[i].events == EPOLLIN && evs[i].data.fd == p[i].fdw)
					{
						read(p[i].fdw,&flag,sizeof(int));
						p[i].busy = 0;
					}
				}
			}
		}
	}
	wait(NULL);
	return 0;
}
