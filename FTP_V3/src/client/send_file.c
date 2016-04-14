#include "head.h"

int send_file(int sfd)
{
	data d;
	bzero(&d,sizeof(d));
	d.len = strlen(DOWNLOAD);
	strcpy(d.buf,DOWNLOAD);
	send_n(sfd,(char*)&d,4+d.len);
	int fd;
	fd = open(DOWNLOAD,O_RDONLY);
	if(-1 == fd)
	{
		perror("open");
		exit(-1);
	}
	int ret;
	while(bzero(&d,sizeof(d)),(d.len = read(fd,d.buf,sizeof(d.buf)))>0)
	{
		ret = send_n(sfd,(char*)&d,4+d.len);
		if(-1 == ret)
	{
			printf("send_n filed\n");
			exit(-1);
		}
		printf("ret = %d\n",ret);
	}
	int flag = 0;
	send_n(sfd,(char*)&flag,sizeof(int));
	close(sfd);
	return 0;
}

int recv_file(int sfd)
{
	int ret;
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
	return 0;
}
