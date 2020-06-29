#include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
       
int binary(int argv[],int key,int n);       
int main(int argc,char *argv[])
{
	int key,n;
	printf("\n%d",argc);
	n=argc;
	int arr1[20];
	printf("\nReceived Array::");
	for(int i=0;i<n;i++)
	{
		arr1[i]=atoi(argv[i]);
		printf("\t%d\t",arr1[i]);	
	}	
	printf("\nEnter the element to be searched::");
	scanf("%d",&key);
	int res=binary(arr1,key,n);
	if(res!=-1)
		printf("\n%d\n",res);
	return 0;
}
int binary(int arr1[],int key,int n)
{
	int last=n-1,first=0,mid=0+(n-1)/2;
	while(first<=last)
	{
		mid=(first+last)/2;
		if(key == arr1[mid])
		{
			printf("NUMBER FOUND");
			return arr1[mid];
		}
		else if(key<arr1[mid])
		{
			last=mid-1;		
		}
		else
		{
			first=mid +1;	
		}	
	}
	printf("NUMBER NOT FOUND");
	return -1;
}	
