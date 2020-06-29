#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>  
int main()
{
	char data[80];
	FILE *fp;
	int j=1;	
	int fd1,l=0,c=0,i=1,fd2;
	int word[20]={0},pass[30];
	int open_mode=O_RDONLY;
	int res=mkfifo("/tmp/my_fifo",0777);
	printf("\nSentences readed are ::");
	
	while(1)
	{
		
		fd1=open("/tmp/my_fifo",O_RDONLY);
		read(fd1,data,80);
		if(data[0]=='$')
		{
			break;
		}
		else
		{	
			fp=fopen("temp.txt","a+");
			if(fp==NULL)
			{
				printf("\nError in opening file");
			}	
			printf("\n%d string :- %s",i,data);
			close(fd1);
			fprintf(fp,"%s",data);
			fclose(fp);
			i++;
		}
		
	}
	fp=fopen("temp.txt","a+");
	char ch,t;
	while((ch = fgetc(fp)) != EOF)
	{	
				
		if(isspace(ch))
		{
			if(isspace(t)==0)
			{		
				(word[j])++;
				printf("\n%d",word[j]);
			}	
		}	
		if(ch=='\n')
		{
			l++;
			j++;
		}	
		t=ch;
	}
	printf("\nNo.of lines are :- %d",l);
	pass[0]=l;
	for(int w=1;w<j;w++)
	{
		printf("\nNo.of words in line %d are :- %d",w,word[w]);
		pass[w]=word[w];
	}
	fp=fopen("temp.txt","w");
	fclose(fp);				
	fd1=open("/tmp/my_fifo",O_WRONLY);
	write(fd1,pass,30);
	close(fd1);	
}	
