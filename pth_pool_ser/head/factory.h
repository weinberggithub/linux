#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef void* (*pfunc)(void*);

typedef struct
{
	pthread_t *pth;
	pfunc p;
	int pnum;
	que_t fque;
	int capability;
	pthread_cond_t cond;
	int flag;
}factory,*pfactory;

void* child_handle(void*);
#endif
