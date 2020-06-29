#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
 

FILE *fp;

int main()
{
	int sz;
	int fd[2],fd1[2];
	char buffer[20];
	char buffer1[20];
	char data1[50];
	char data[50];
	if(pipe(fd)!=0)
	{
		printf("\npipe creation error");
	}	
	if(pipe(fd1)!=0)
	{
		printf("\npipe creation error");
	}
	pid_t p;
	p=fork();
	if(p<0)
	{
		printf("\nprocess creation failed");
	}	
	else if(p==0)
	{
		printf("\nChild process is running");
		close(fd[1]);
		sz=read(fd[0],buffer1,20);
		close(fd[0]);
		printf("\nPassed filename is %s",buffer1);
		
		fp=fopen(buffer1,"r");
		
		if(fp==NULL)
		{
			printf("\nFailed to open the file");
		}
		else
		{
			printf("\nIn Child,file contents are:- ");
			while( fgets (data,50, fp )!= NULL ) 
			   { 
			
				  // Print the file contents
				  printf( "\n%s" , data ) ; 
			   }
		   fclose(fp); 
		} 
		
		sz=write(fd1[1],data,50);
		printf("\nChild has sent the file contents to parent");
	}
	else
	{
		printf("\nParent process is running");
		printf("\nEnter the filename::");
		scanf("%s",buffer);
		close(fd[0]);
		sz=write(fd[1],buffer,20);
		close(fd[1]);	
		wait(NULL);
		//sleep(5);
		close(fd1[1]);
		sz=read(fd1[0],data1,50);
		if(sz==-1)
		{
			printf("\nError");
		}
		close(fd1[0]);	
		printf("\nIn Parent,contents of file :- %s",data1);
		
		exit(EXIT_SUCCESS);
	}
	
}			
