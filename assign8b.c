#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>	
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "shm1.h"
#include <sys/shm.h>

int main()
{
	struct shared_memory1 *p,*share;
	int shmid;
	
	shmid=shmget((key_t)1234,sizeof(struct shared_memory1),0666 | IPC_CREAT);
	if (shmid == -1) 
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	printf("shmid %d",shmid);
	share= shmat(shmid, (void *)0, 0);
	if (share ==(void *)-1) 
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", (int)share);
	
	p=(struct shared_memory1 *)share;
	p->written_by_you=0;
	while(1)
	{
		if(p->written_by_you)
		{
			printf("\nText Written is :- %s",p->some_text);		
			sleep(rand()%4);	
			p->written_by_you=0;
			if(strncmp(p->some_text,"end",3)==0)
				break;		
		}
	}
	if (shmdt(p) == -1) 
	{
		fprintf(stderr,"shmdt failed\n");	
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1) 
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
	}		
			
}			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	
