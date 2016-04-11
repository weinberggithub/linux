#include"factory.h"

void que_init(pque pq)
{
	pq->head = NULL;
	pq->tail = NULL;
	pthread_mutex_init(&pq->mutex,NULL);
	pq->size = 0;
}

void que_insert(pque pq,pnode pnew)
{
	pthread_mutex_lock(&pq->mutex);
	if(pq->size == 0)
	{
		pq->head = pnew;
		pq->tail = pnew;
	}else
	{
		pq->tail->pnext = pnew;
		pq->tail = pnew;
	}
	pq->size++;
	pthread_mutex_unlock(&pq->mutex);
}

void que_get(pque pq,pnode* pget)
{
	pque pq = &pf->fque;
	pthread_mutex_lock(&pq->mutex);
	while(pq->size == 0)
	{
		pthread_cond_wait(&pf->cond,&pq->mutex);
	}
	*pget = pq->head;
	pq->head = pq->head->pnext;
	pq->size--;
	if(pq->size == 0)
	{
		pq->tail = NULL;
	}
	pthread_mutex_unlock(&pq->mutex);
	printf("i can be here\n");
}
