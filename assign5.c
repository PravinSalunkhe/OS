#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void * reader(void *a1);
void *writer(void *a2);
pthread_mutex_t mutex1;
sem_t wrt;
int readcount,k=0;
int main()
{
	int m,n,res;
	int *ptr;
	void *thread_result;
	printf("\nEnter the no of readers::");
	scanf("%d",&m);
	printf("\nEnter the no of writers");
	scanf("%d",&n);
	pthread_t r[m],w[n];
	res=sem_init(&wrt,0,1);
	if (res != 0)
	{
		perror("full initialization failed");
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<m;i++)
	{
		int *ptr[10]={&k,&i};
		res=pthread_create(&r[i],NULL,reader,(void*)ptr);
		sleep(2);
	}	
	for(int i=0;i<n;i++)
	{
		int *ptr[10]={&k,&i};
		res=pthread_create(&w[i],NULL,writer,(void*)ptr);
		sleep(2);
	}	
	for(int i=0;i<m;i++)
	{
		res=pthread_join(r[i],&thread_result);
	}
	for(int i=0;i<n;i++)
	{
		res=pthread_join(w[i],&thread_result);
	}
		
}
void * reader(void *a1)
{
	int **p=(int **) a1;
	//int k=*(p[0]);
	int i=*(p[1]);
	
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		readcount++;
		if(readcount==1)
			sem_wait(&wrt);
		pthread_mutex_unlock(&mutex1);
					
		printf("\nReader[%d] has finished reading.\nvalue of var is %d",i,k);
		
		pthread_mutex_lock(&mutex1);
		readcount--;
		if(readcount==0)
			sem_post(&wrt);
		pthread_mutex_unlock(&mutex1);
		sleep(rand()%5);
	}
}			
void *writer(void *a2)
{
	int **p=(int **) a2;
	//int k=*(p[0]);
	int i=*(p[1]);
	
	while(1)
	{
		sem_wait(&wrt);
		printf("\nWriter[%d] wants to write",i);
		k++;
		printf("New value of var is %d",k);
		sem_post(&wrt);
		sleep(rand()%5);
	}
}	
	
	
	
		
			
