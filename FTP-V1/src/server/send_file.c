#include "head.h"

void send_file(int sfd)
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
}
