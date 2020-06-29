#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

sem_t m[5];
pthread_mutex_t mutex1;
typedef enum{thinking,hungry,eating}e;
e state[5];
void * thread_function(void *arg);
void pickup(int i);
void test(int i);
void putdown(int i);
void initialize();
int main()
{
	int res;
	void * thread_result;
	pthread_t phil[5];
	for(int i=0;i<5;i++)
	{
		res=sem_init(&m[i],0,1);
		if (res != 0)
		{
			perror("semaphore initialization failed");
			exit(EXIT_FAILURE);
		}
	}
	for(int i=0;i<5;i++)
	{
		int * ptr=&i;
		res = pthread_create(&phil[i], NULL, thread_function, (void *)ptr);
		if (res != 0)
		{
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
			
		}
		printf("\n\n****Thread %d has been created****",i);
		sleep(1);
	}	
	for(int i=0;i<5;i++)
	{
		res = pthread_join(phil[i], &thread_result);
		if (res != 0) 
		{
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}	
	
}
void * thread_function(void *arg)
{
	int i=*(int *) arg;
	state[i]=thinking;
	while(1)
	{
		sleep(1);
		//printf("\nPhilosopher[%d] is thinking",i);
		pickup(i);
		
		sleep(2);
		
		putdown(i);
	}	
}	
void initialize()
{
	for(int i=0;i<5;i++)
	{
		state[i]=thinking;
	}	
}		
void pickup(int i)
{
	pthread_mutex_lock(&mutex1);
	state[i]=hungry;
	printf("\n\nPhilosopher[%d] wants to eat",i);
	test(i);
	pthread_mutex_unlock(&mutex1);
	if(state[i]!=eating)
	{
		sem_wait(&m[i]);
	}
	
}
void test(int i)
{
	if(state[(i+4)%5]!=eating &&  state[i]==hungry &&  state[(i+1)%5]!=eating)
	{
		state[i]=eating;
		printf("\n\nPhilosopher[%d] is eating",i);
			sem_post(&m[i]);	
	}
}		

void putdown(int i)
{	
	pthread_mutex_lock(&mutex1);	
	state[i]=thinking;
	printf("\n\nPhilosopher[%d] has finished eating",i);
	//sem_post(&m[i]);
	test((i+4)%5);
	test((i+1)%5);
	pthread_mutex_unlock(&mutex1);
	//printf("\n\nPhilosopher[%d] has finished eating",i);
}




			
	
	
	
