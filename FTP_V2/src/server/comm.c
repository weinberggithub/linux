#include "factory.h"

void comm_func(pcomm comm,pfactory pf,pnode pget)
{
	int ret;
	switch(comm->key)
	{
		case 1:ls_func(pf,pget);break;
		case 2:cd_func(pf,pget);break;
		case 3:pwd_func(pf,pget);break;
		case 4:rm_func(pf,pget);break;
		case 5:puts_func(pf,pget);break;
		case 6:gets_func(pf,pget);break;
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
			send_n(pget->new_fd,(char*)&d,4+d.len);
			printf("%s",buf);
		}
	}
	d.len = 0;
	d.buf = {0};
	send_n(pget->new_fd,(char*)&d,strlen(d.buf));
	closedir(pdir);
	return 0;
}
void cd_func()
{
	
}
