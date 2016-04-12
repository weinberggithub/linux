#include "head.h"

//void iscomm(char *comm,int pos,pcomm pc)
//{
	
//}
int comm_analyze(char *strbuf,data comm_d)
{
	int i = 0;
	int j = 0;
	pcomm pc;
	bzero(pc,sizeof(comm));
	while(strbuf[i] != ' ' && strbuf[i] != '\n')
	{
		i++;
//		printf("%d\n",i);
	}
//	printf("%d\n",i);
	if(!strncmp("ls",strbuf,i))
	{
		pc->key = 1;
		for(i = i + 1;i< strlen(strbuf) - 1;i++)
		{
			pc->comm_argc[j] =strbuf[i];
			j++;
		}
	}else{
		return -1;
	}
	comm_d.len = pc->key;
	comm_d.flags = 0;
	strcpy(comm_d.buf,pc->comm_argc);
//	printf("comm analyze success!\n");
	return 0;
}
