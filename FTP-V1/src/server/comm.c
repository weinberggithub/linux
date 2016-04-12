#include "factory.h"

void comm_func(data *comm_d,pfactory pf,pnode pget)
{
	int ret;
	if(comm_d->flags == 2)
	{
		
	}else if(comm_d->flags == 1){
		
	}else if(comm_d->flags == 0){
//		printf("%s\n",pf->pth_pwd);
		ret = ls_func(pf,pget);
	}
}
int ls_func(pfactory pf,pnode pget)
{
	DIR *pdir;
	//printf("%s\n",pf->pth_pwd);
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
			send(pget->new_fd,buf,sizeof(buf),0);
//			printf("%s",buf);
			sleep(1);
		}
	}
	closedir(pdir);
	return 0;
}
