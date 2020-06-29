#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

       int main(int argc, char *argv[])
       {
       	   
           pid_t cpid;
           cpid=fork();
           if(cpid<0)
           	printf("Error");
           else if(cpid==0)
           {
           		printf("\nChild process is running");
           		
           		printf("\nchild id:: %d",getpid());
           		printf("\nOldparent id ::%d",getppid());
           		sleep(20);
           		printf("\nnewparent id ::%d",getppid());
           }
           else
           {
		printf("\nparent is running");
		printf("parent id is %d ",getpid());	
		exit(0);
           }
           return 0;
        }   			
       
