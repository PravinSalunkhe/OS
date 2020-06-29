#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int sum=0;
void *thread_function(void *arg);
void create(int *mat,int row,int column)//get the elements of matrix
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			printf("\nEnter the element[%d][%d]::",i,j);
			scanf("%d",(mat+i*column+j));
		}
	}
}
int main()
{
	int res,r1,c1,r2,c2;
	int *mat1,*mat2;
	clock_t start,end,total;
	int mat3[20][20];
	pthread_t a[20][20];
	void *thread_result;
	printf("\nEnter the size of mat1::");
	scanf("%d%d",&r1,&c1);
	printf("\nEnter the size of mat2::");
	scanf("%d%d",&r2,&c2);
	if(c1==r2)
	{	
		mat1=(int*)malloc(r1*c1*sizeof(int));
		mat2=(int*)malloc(r2*c2*sizeof(int));
		printf("Matrix 1");
		create(mat1,r1,c1);
		printf("Matrix 2");
		create(mat2,r2,c2);
		start=clock();
		for(int i=0;i<r1;i++)
		{
			
			for(int j=0;j<c2;j++)
			{
				
				int *ptr[20]={mat1,mat2,&r1,&c1,&r2,&c2,&i,&j};
				res=pthread_create(&a[i][j],NULL,thread_function,(void*)ptr);
				if (res != 0) 
				{
					perror("thread creation failed");
					exit(EXIT_FAILURE);
				}
				sleep(2);
				res = pthread_join(a[i][j],&thread_result);
				if (res != 0)
				{
					perror("Thread join failed");
					exit(EXIT_FAILURE);
				}
				//printf("\t%d",*(int*)thread_result);
				mat3[i][j]=*(int*)thread_result;
			}
		}
		end=clock();
		total= (double)(end- start);
		printf("\nResult of Matrix Multiplication-->");
		for(int i=0;i<r1;i++)
		{
			printf("\n");
			for(int j=0;j<c2;j++)
			{
				printf("\t%d",mat3[i][j]);
			}
		}
	}	
	printf("\n");
	printf("\nTime taken is %ld",total);
}
void *thread_function(void *arg)
{
	int **p=(int**)arg;
	int *a1=p[0];
	int *a2=p[1];
	int r1=*(p[2]);
	int c1=*(p[3]);
	int r2=*(p[4]);
	int c2=*(p[5]);
	int i=*(p[6]);
	int j=*(p[7]);
	sum=0;
	printf("\nThread[%d][%d]created.",i,j);
	for(int k=0;k<c1;k++)
	{
		sum=sum + (*(a1+i*c1+k) * *(a2+k*c2+j)); 
	}
	printf("\nmat[%d][%d]:: %d",i,j,sum);
	int *m=(int*)malloc(sizeof(sum));
	m=&sum;
	pthread_exit((void*)m);

}
