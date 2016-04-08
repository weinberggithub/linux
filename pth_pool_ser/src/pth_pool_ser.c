#include "factory.h"

int main(int argc,char* argv[])
{
	if(argc != 5)
	{
		printf("argc error\n");
		return -1;
	}
	int num = atoi(argv[3]);
	int cap = atoi(argv[4]);
	factory f;
	factory_init(&f,child_handle,num,cap);
	factory_start(&f);
	int sfd = socket(AF_INET,SOCK_STREAM,0);
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
	if(ret == -1)
	{
		perror("epoll_create");
		return -1;
	}
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	pnode pnew;
	while(1)
	{
		ret = epoll_wait(epfd,&event,1,-1);
		if(ret > 0)
		{
			if(event.events == EPOLLIN && event.data.fd == sfd)
			{
				pnew = (pnode)malloc(sizeof(node_t));
				pnew->new_fd = accept(epfd,NULL,NULL);
				que_insert(&f.fque,pnew);
				pthread_cond_signal(&f.cond);			
			}
		}
	}
}

void* child_handle(void* p)
{
	pfactory pf = (pfactory)p;
	pnode pget;
	while(1)
	{
		que_get(pf,&pget);
		send_file(pget->new_fd);
		free(pget);
	}
}
