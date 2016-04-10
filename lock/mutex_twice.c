#include<pthread.h>
#include<stdio.h>
#include<string.h>

pthread_mutex_t mutex;
void *pfunc(void *p)
{
	printf("i am at out\n");
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	printf("here is the recursive lock\n");
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	printf("i am awake\n");
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_mutexattr_t ma;
	ret = pthread_mutexattr_settype(&ma,PTHREAD_MUTEX_RECURSIVE_NP);
	printf("ret= %d\n",ret);
	pthread_mutex_t mutex;
	ret = pthread_mutex_init(&mutex,&ma);
	printf("init ret is%d\n",ret);
	pthread_t pth_id;
	ret = pthread_create(&pth_id,NULL,pfunc,NULL);
	if(ret != 0)
	{
		printf("thread create filed\n");
		return -1;
	}
	ret = pthread_join(pth_id,NULL);
	if(ret != 0)
	{
		printf("pthread_join error");
		return -1;
	}
	ret = pthread_mutex_destroy(&mutex);
	if(ret != 0)
	{
		printf("destroyed filed\n");
		return -1;
	}
	pthread_cancel(pth_id);
	return 0;
	
}
