#include<pthread.h>
#include<stdio.h>
int sum = 0;
pthread_mutex_t mutex;

void* pfunc(void* p)
{
		pthread_mutex_lock(&mutex);
		printf("i can be here\n");
		pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
int main()
{
	pthread_mutex_init(&mutex,NULL);
	
	pthread_t pth_id;
	int ret;
	pthread_create(&pth_id,NULL,pfunc,NULL);
//	if(ret > 0)
//	{
//		printf("thread1 create filed");
//		return -1;
//	}
	ret =  pthread_join(pth_id,NULL);
//	if(ret > 0)
//	{	
//		printf("thread2 create filed");
//		return -1;
//	}
	pthread_mutex_destroy(&mutex);
	pthread_cancel(pth_id);
	return 0;
}
