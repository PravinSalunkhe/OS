#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
  
int main()
{
	char arr[80];
	int fd,fp,fd3;
	int pass1[30];
	int open_mode=O_WRONLY;
	int res=mkfifo("/tmp/my_fifo",0777);
	if(res==0)
	{
		printf("\nFIFO created");
	}
	printf("\nEnter the sentences to write to other process.\nEnter '$' to finish\n");
	while(1)
	{
		
		fd=open("/tmp/my_fifo",O_WRONLY);
		fgets(arr,80,stdin);
		//printf("%s",arr);
		if(arr[0]=='$')
		{
			write(fd,arr,strlen(arr)+1);
			close(fd);	
			break;
		}
		else
		{
			write(fd,arr,strlen(arr)+1);
			close(fd);
		}	
			
	}
	printf("\ndsffdsfd");
	fd=open("/tmp/my_fifo",O_RDONLY);
	read(fd,pass1,30);
	printf("\nNo.of lines are :- %d",pass1[0]);
	for(int w=1;w<=pass1[0];w++)
	{
		printf("\nNo.of words in line %d are :- %d",w,pass1[w]);
		printf("\n");
	}
	return 0;
	
}		


