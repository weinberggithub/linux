#include "head.h"

//void iscomm(char *comm,int pos,pcomm pc)
//{

	
//}
//void comm_error()
//{
	
//}

/*
	comm_analyze函数：解析命令
*/
int comm_analyze(char *strbuf,pcomm pc)
{
	int i = 0;
	int j = 0;
	while(strbuf[i] != ' ' && strbuf[i] != '\n')
	{
		i++;
	}
	if(!strncmp("ls",strbuf,2))
	{
		pc->key = 1;
		bzero(&pc->argc,sizeof(pc->argc));
		return 0;
	}else if(!strncmp("cd",strbuf,2)){
		pc->key = 2;
		strncpy(pc->argc,strbuf+4,strlen(strbuf)-2);
	return 0;
	}else if(!strncmp("pwd",strbuf,3)){
		pc->key = 3;
		bzero(&pc->argc,sizeof(pc->argc));
		return 0;
	}else if(!strncmp("rm",strbuf,2)){
		pc->key = 4;
		strncpy(pc->argc,strbuf+4,strlen(strbuf)-2);
		return 0;
	}else if(!strncmp("puts",strbuf,4)){
		pc->key = 5;
		strncpy(pc->argc,strbuf+6,strlen(strbuf)-2);
		return 0;
	}else if(!strncmp("gets",strbuf,4)){
		pc->key = 6;
		strncpy(pc->argc,strbuf+6,strlen(strbuf)-2);
		return 0;
	}else{
		return -1;
	}
}

