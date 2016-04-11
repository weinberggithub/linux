#ifndef __WORK_H__
#define __WORK_H__
#include "head.h"

typedef struct node
{
int new_fd;
	struct node* pnext;
}*pnode,node_t;
typedef struct
{
	pnode head,tail;
	pthread_mutex_t mutex;
	int isnull;
	int size;
}que_t,*pque;

void que_init(pque);
#endif
