#include "dlser_head.h"

void mkchild(pchild p,int num)
{
	int fds[2];
	pid_t pid;
	int i;
	for(i = 0;i < num;i++)
	{
		if(!(pid = fork()))
		{
			close(fds[1]);
			child_handle(fds[0]);
		}
		p[i].pid = pid;
		p[i].fdw = fds[1];
		p[i].busy = 0;
	}
}

void child_handle(int fdr)
{
	int newfd;
	int flag = 1;
	while(1)
	{
		recv_fd(fdr,&newfd);
		send_file(newfd);
		write(fdr,&flag,sizeof(int));
	}
}
