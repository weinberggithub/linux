#include "factory.h"

void comm_func(pcomm pc,pfactory pf,pnode pget)
{
	int ret;
	switch(pc->key)
		{
		case 1:ls_func(pf,pget);break;
		case 2:cd_func(pc,pf,pget);break;
		case 3:pwd_func(pf,pget);break;
		case 4:rm_func(pc,pf,pget);break;
		case 5:puts_func(pc,pf,pget);break;
		case 6:gets_func(pc,pf,pget);break;
	}
}
int ls_func(pfactory pf,pnode pget)
{
	DIR *pdir;
	pdir = opendir(pf->pth_pwd);
	printf("%s\n",pf->pth_pwd);
	if(pdir == NULL)
	{
		perror("opendir");
		return;
	}
	struct dirent *dirinfo;
	char buf[128] = {0};
	struct stat fsta;
	int ret;
	char ftype;
	data d;
	while((dirinfo = readdir(pdir))!= NULL)
	{
		sprintf(buf,"%s/%s",pf->pth_pwd,dirinfo->d_name);
		ret = stat(buf,&fsta);
		bzero(buf,sizeof(buf));
		if(!strcmp(dirinfo->d_name,".") || !strcmp(dirinfo->d_name,".."))
		{
		}else{
			sprintf(buf,"%-5s %-10s		%-10ld\n",dirinfo->d_type>4?"-":"d",dirinfo->d_name,fsta.st_size);
			d.len = strlen(buf);
			strcpy(d.buf,buf);
			printf("---------------\n");
			ret = send_n(pget->new_fd,(char*)&d,4+d.len);
			if(ret == -1)
			{
				perror("send");
				return -1;
			}
			printf("%s",buf);
		}
	}
	d.len = 0;
	bzero(&d.buf,sizeof(d.buf));
	send_n(pget->new_fd,(char*)&d,strlen(d.buf));
	closedir(pdir);
	return 0;
}
int cd_func(pcomm pc,pfactory pf,pnode pget)
{
	int ret;
	char buf[1024] = {0};
	sprintf(buf,"%s/%s",pf->pth_pwd,pc->argc);
	ret = chdir(buf);
	printf("%s\n",getcwd(NULL,0));
	strcpy(pf->pth_pwd,getcwd(NULL,0));
	return 0;
}

int pwd_func(pfactory pf,pnode pget)
{
	data d;
	bzero(&d,sizeof(d));
	getcwd(d.buf,0);
	printf("%s\n",d.buf);
	d.len = sizeof(d.buf);
	send_n(pget->new_fd,(char*)&d,strlen(d.buf));
	return 0;
}

int rm_func(pcomm pc,pfactory pf,pnode pget)
{
	
	unlink(pc->argc);
	send(pget->new_fd,"remove success !",16,0);
	return 0;
}

int puts_func(pcomm pc,pfactory pf,pnode pget)
{
	int ret;
	ret = recv_file(pget->new_fd);
	if(ret == 0)
	{
		printf("puts success !\n");
		send(pget->new_fd,"puts success !",16,0);
	}
		return 0;
}

int gets_func(pcomm pc,pfactory pf,pnode pget)
{
	int ret;
	ret = send_file(pget->new_fd);
	if(ret == 0)
	{
		printf("gets success !\n");
		send(pget->new_fd,"puts success !",16,0);
	}
		return 0;
}
