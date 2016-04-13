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
int comm_analyze(char *strbuf,pcomm comm)
{
	int i = 0;
	int j = 0;
	while(strbuf[i] != ' ' && strbuf[i] != '\n')
	{
		i++;
	}
	if(!strncmp("ls",strbuf,2))
	{
		comm->key = 1;
		comm->cm = "ls";
		comm->argc = NULL;
		return 0;
	}else if(!strncmp("cd",strbuf,2)){
		comm->key = 2;
		comm->cm = "cd";
		strncpy(comm->argc,strbuf+4,strlen(strbuf)-2);
	return 0;
	}else if(!strncmp("pwd",strbuf,3)){
		comm->key = 3;
		comm->cm = "pwd";
		comm->argc = NULL;
		return 0;
	}else if(!strncmp("rm",strbuf,2)){
		comm->key = 4;
		comm->cm = "rm";
		strncpy(comm->argc,strbuf+4,strlen(strbuf)-2);
		return 0;
	}else if(!strncmp("puts",strbuf,4)){
		comm->key = 5;
		comm->cm = "puts";
		strncpy(comm->argc,strbuf+6,strlen(strbuf)-2);
		return 0;
	}else if(!strncmp("gets",strbuf,4)){
		comm->key = 6;
		comm->cm = "gets";
		strncpy(comm->argc,strbuf+6,strlen(strbuf)-2);
		return 0;
	}else{
		return -1;
	}
}

/*
	ls功能：显示当前目录的所有文件和目录
*/
//int ls_func(int sfd,data *comm_d)
//{
//	int ret;
//	char buf[128] = {0};
//	ret = send(sfd,comm_d,sizeof(comm_d),0);
//	if(ret == -1)
//	{
//		perror("send");
//		return;
//	}
//	while(bzero(&buf,sizeof(buf)),(ret = recv(sfd,buf,sizeof(buf),0))> 0)
//	{
//		printf("%s",buf);
//	}
//	return 1;


