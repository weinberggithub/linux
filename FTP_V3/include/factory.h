#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

#define PWDLEN 128

typedef void* (*pfunc)(void*);

typedef struct
{
	pthread_t *pth;
	pfunc p;
	int pnum;
	que_t fque;
	int capability;
	pthread_cond_t cond;
	char pth_pwd[PWDLEN];
	int flag;
}factory,*pfactory;

void comm_func(pcomm,pfactory,pnode);
void* child_handle(void*);
int ls_func(pfactory,pnode);
int cd_func(pcomm,pfactory,pnode);
int pwd_func(pfactory,pnode);
int rm_func(pcomm,pfactory,pnode);
int puts_func(pcomm,pfactory,pnode);
int gets_func(pcomm,pfactory,pnode);
#endif
