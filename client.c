#include "head.h"

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
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(0,&rdset);
		FD_SET(sfd,&rdset);
		ret = select(sfd + 1,&rdset,NULL,NULL,NULL);
		if(ret > 0)
		{
			if(FD_ISSET(0,&rdset))
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
			if(FD_ISSET(sfd,&rdset))
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

