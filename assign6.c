#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chop[5];
void * thread_func(void *arg);
void *thread_result;
int main()
{
	int res;
	pthread_t phil[5];
	for(int i=0;i<5;i++)
	{
		res=sem_init(&chop[i],0,1);
		if(res!=0)
		{
			printf("\nsemaphore initialization failed");
			exit(EXIT_FAILURE);	
		}	
	}
	//printf("df sfd");
	for(int i=0;i<5;i++)
	{
		int *ptr=&i;
		res=pthread_create(&phil[i],NULL,thread_func,(void*) ptr);	
		if(res!=0)
		{
			printf("\nthread creation failed");
			exit(EXIT_FAILURE);	
		}
	}
	for(int i=0;i<5;i++)
	{
		res=pthread_join(phil[i],&thread_result);	
		if(res!=0)
		{
			printf("\nthread join failed");
			exit(EXIT_FAILURE);	
		}
	}
	return 0;	
}	
void * thread_func(void *arg)
{
	int *ptr=(int *)arg;
	int i=*(ptr);
	
	while(1)
	{
		if((i%2)==0)
		{
			sem_wait(&chop[i]);
			sem_wait(&chop[(i+1)%5]);
		}
		else
		{
			sem_wait(&chop[(i+1)%5]);
			sem_wait(&chop[i]);
		}
		
				
			printf("\nPhilosopher[%d] is eating",i);
			sleep(rand()%4);	
			
			sem_post(&chop[i]);
			sem_post(&chop[(i+1)%5]);
		
		printf("\nPhilosopher[%d] has finished eating\n",i);	
		sleep(rand()%5);		
	}	

}	
	

