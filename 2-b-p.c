 #include <sys/types.h>
 #include <sys/wait.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
       
void bubble(int arr[],int n);
int main(int argc, char *argv[])
{
   pid_t cpid;
   int n,i;
   int arr[20];
    char *a[20];
   char str[20];
   printf("\nEnter the no of elements::");
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
	printf("\nEnter the no::");
	scanf("%d",&arr[i]);
   }	
   bubble(arr,n);
  
   for(i=0;i<n;i++)
   {
   	sprintf(str,"%d",arr[i]);
   	a[i]=(char*)malloc(sizeof(str));
   	strcpy(a[i],str);
   }	
	a[i]=NULL;
   cpid=fork();
   if(cpid<0)
   	printf("Error");
   else if(cpid>0)
   {
   	  // print the sorted array
    printf("\nSorted Array: ");
    for(int i = 0; i < n; i++)
    {
	printf("%d  ", arr[i]);
    }
    wait(NULL);	
   }
   else
   {
    	
    	sleep(5);
   	execv("./p2",a);	
   }
   return 0;
}   			
void bubble(int arr[20],int n)
{
  int i, j, temp;
  for(i = 0; i < n; i++)
  {
      for(j = 0; j < n-i-1; j++)
      {
          if( arr[j] > arr[j+1])
          {
              // swap the elements
              temp = arr[j];
              arr[j] = arr[j+1];
              arr[j+1] = temp;
          } 
      }
  }
}      
