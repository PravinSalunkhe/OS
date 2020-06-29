#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "shm1.h"
#include <sys/shm.h>

/*typedef struct shared_memory1 
{
	int written_by_you;
	char data[TEXT_SZ];
};*/
int main() 
{
	struct shared_memory1 *p,*share;
	int shmid;
	char buffer[300];
	
	shmid=shmget((key_t)1234,sizeof(struct shared_memory1),0666 | IPC_CREAT);
	if (shmid == -1) 
	{
		printf("shmget failed\n");
		exit(EXIT_FAILURE);
	}
	printf("shmid %d",shmid);
	share= shmat(shmid, NULL, 0);
	if (share== (void *)-1) {
		printf( "\nshared memory attachment to process failed\n");
		exit(EXIT_FAILURE);
	}
	printf("\nmemory attached at %d",((int*)share));
	p=share;
	
	while(1)
	{
		if(share->written_by_you==1)
		{
			printf("\nwait for client");
			sleep(1);
		}
		printf("enter the text:- ");
		fgets(buffer,300,stdin);
		strncpy(p->some_text,buffer,TEXT_SZ);
		p->written_by_you=1;
		if (strncmp(buffer, "end", 3) == 0) 
			break;	
	}		
	if(shmdt(p)==-1)
	{
		printf("\nFailed to detach shared memory");
	}
	return 0;				
}








