#include "head.h"

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
	fd_set rdset;
	fd_set newset;
	int maxfd;
	FD_ZERO(&newset);
	char buf[128] = {0};
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&newset);
		FD_SET(sfd,&newset);
		memcpy(&rdset,&newset,sizeof(rdset));
		if(FD_ISSET(newfd,&newset))
		{
			maxfd = newfd + 1;
		}else{
			maxfd = sfd + 1;
		}
		ret = select(maxfd,&rdset,NULL,NULL,NULL);
		if(ret > 0)
		{
			if(FD_ISSET(sfd,&rdset))
			{
				newfd = accept(sfd,(struct sockaddr*)&client,&addrlen);
				if(newfd == -1)
				{
					perror("accept");
					exit(-1);
				}
				printf("client ip=%s port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
				FD_SET(newfd,&newset);
			}
			if(FD_ISSET(newfd,&rdset))
			{
				bzero(buf,sizeof(buf));
				ret = recv(newfd,buf,sizeof(buf),0);
				if(ret < 0)
				{
					perror("recv");
					exit(-1);
				}else if(ret == 0)
				{
					close(newfd);
					FD_CLR(newfd,&newset);
				}else{
					printf("%s\n",buf);
				}
			}
		}
		if(FD_ISSET(0,&rdset))
		{	
			bzero(buf,sizeof(buf));
			read(0,buf,sizeof(buf));
			ret = send(newfd,buf,strlen(buf) - 1,0);
			if(ret == -1)
			{
				perror("sened");
				exit(-1);
			}
		}
	}
	close(sfd);
	return 0;
}
