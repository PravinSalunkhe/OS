#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *producer(void *a1);
void *consumer(void *a2);
pthread_mutex_t mutex1;
sem_t empty,full;
int front=0,rear=0;
int main()
{
	int m,n,res;	

	int buffer[10];
	printf("\nEnter the no of producers::");
	scanf("%d",&m);
	printf("\nEnter the no of consumers::");
	scanf("%d",&n);
	pthread_t p[m];
	pthread_t c[n];
	void *thread_result;
	res = sem_init(&full, 0, 0);
	if (res != 0)
	{
		perror("full initialization failed");
		exit(EXIT_FAILURE);
	}
	res=sem_init(&empty,0,10);
	if (res != 0)
	{
		perror("empty initialization failed");
		exit(EXIT_FAILURE);
	}
	
	for(int i=0;i<m;i++)
	{
		int *ptr[10]={buffer,&i};
		res=pthread_create(&p[i],NULL,producer,(void*)ptr);
	}		
	
	for(int i=0;i<n;i++)
	{
		int *ptr[10]={buffer,&i};
		res=pthread_create(&c[i],NULL,consumer,(void*)ptr);
	}		
	for(int i=0;i<m;i++)
	{
		res=pthread_join(p[i],&thread_result);
		printf("\nproducer has returned");
	}	
	for(int j=0;j<n;j++)
	{
		res=pthread_join(c[j],&thread_result);
		printf("\nconsumer has returned");
	}	
}
void *producer(void *a1)
{
	int **p=(int**)a1;
	int *arr=p[0];
	int i=*(p[1]);
	
	int j;
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex1);
		printf("\nProducer[%d] has produced an item.",i);
		printf("\nproducer[%d] wants to add an item",i);
		
		*(arr+rear)=rand()%10;
		printf("\nADDED ITEM-->");
		printf("%d",*(arr+rear));
		rear=(rear+1)%10;
			
		printf("\nBUFFER  ");
		sleep(1);
		for(int j=front;j<rear;j++)
		{
			printf("\t%d",*(arr+j));
		}
		
		printf("\nproducer[%d] has added an item to the buffer\n",i);
		pthread_mutex_unlock(&mutex1);
		sem_post(&full);
		sleep(rand()%10);
	}
	
	pthread_exit(NULL);
}
void *consumer(void *a2)
{
	int **p=(int**)a2;
	int *arr=p[0];
	int i=*(p[1]);
	int j;
	while(1)
	{
		
		sem_wait(&full);
		pthread_mutex_lock(&mutex1);
		printf("\nConsumer[%d] wants to  remove the item from the buffer",i);
		int x=*(arr+front);
		front=(front+1)%10;
		if(front==rear)
		{
			rear=0;
			front=0;
		}	
		printf("\nREMOVED ITEM-->");
		printf("%d",x);
		printf("\nBUFFER  ");
		sleep(1);
		for(int j=front;j<rear;j++)
		{
			printf("\t%d",*(arr+j));
		}	
		
		printf("\nConsumer[%d] has removed an item from the buffer.Consumer has consumed it\n",i);
		pthread_mutex_unlock(&mutex1);
		sem_post(&empty);
		sleep(rand()%10);
	}
	pthread_exit(NULL);
}
		 
	
	
	
	
	
	
	
	
		
	
