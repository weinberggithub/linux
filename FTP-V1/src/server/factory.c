#include "factory.h"

void factory_init(pfactory pf,pfunc pth_pfunc,int pth_num,int cap,char *pwd)
{
	pf->pth = (pthread_t*)malloc(pth_num*sizeof(pthread_t));
	pf->p = pth_pfunc;
	pf->pnum = pth_num;
	pf->capability = cap;
	pthread_cond_init(&pf->cond,NULL);
	pf->flag = 0;
	que_init(&pf->fque);
	strcpy(pf->pth_pwd,pwd);
//	printf("%s\n",pf->pth_pwd);
}

void factory_start(pfactory pf)
{
	int i;
	int ret;
	for(i = 0;i < pf->pnum;i++)
	{
		ret = pthread_create(&(pf->pth)[i],NULL,pf->p,(void*)pf);
		if(ret != 0)
		{
			printf("pthread_create failed ret=%d\n",ret);
			exit(-1);
		}
	}
	pf->flag = 1;
}
