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

void comm_func(data*,pfactory,pnode);
void* child_handle(void*);
int ls_func(pfactory,pnode);
#endif
