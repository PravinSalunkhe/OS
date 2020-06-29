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
           		printf("\nparent id ::%d",getppid());
           		sleep(1);
           		//printf("\nnewparent id ::%d",getppid());
           }
           else
           {
			printf("\nparent is running");	
           		sleep(10);
           		wait(NULL);
           }
        }   			
       
