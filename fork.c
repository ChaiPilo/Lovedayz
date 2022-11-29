#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>   
#include <sys/wait.h>
#include <unistd.h>
#define MAX 20
void bubble_asc(int arr[],int n)
{ 
int i,j,temp;
for(i=0;i<n;i++)
{
    for(j=0;j<n-i-1;j++)
    {
        if(arr[j]>arr[j+1])
	{
	    temp=arr[j];
	    arr[j]=arr[j+1];
	    arr[j+1]=temp;
	}
    }
}
}
void bubble_dsc(int arr[],int n)
{ 
int i,j,temp;
for(i=0;i<n;i++)
{
    for(j=0;j<n-i-1;j++)
    {
        if(arr[j]<arr[j+1])
	{
	    temp=arr[j];
	    arr[j]=arr[j+1];
	    arr[j+1]=temp;
	}
    }
}
}
void print(int arr[],int n)
{
   int i;
   for(i=0;i<n;i++)
   {
       printf("\t%d",arr[i]);
   }
   printf("\n\n");
}
int main()
{
   int i,n,pid,f,arr[MAX];
   printf("\nHOW MANY NOS DO YOU WANT IN ARRAY : ");
   scanf("%d",&n);
   printf("ENTER ARRAY ELEMENT : ");
   for(i=0;i<n;i++)
   {
       scanf("%d",&arr[i]);
   }
   pid=fork();
        if(pid==0)
        {
              sleep(3);
              printf("\nchild process pid id:%d ",getpid());
              printf("\nParrent process pid id:%d ",getppid());
              printf("\nArray in ascending order..\n");
              bubble_asc(arr,n);
		print(arr,n);
               system("ps -el | grep init");
              
        }
        
        else if(pid>0)
        {
        //	system("ps -el | grep Z");
        	//f=wait(0);
        //	printf("\nTerminated child pid is: %d ",f);
        	printf("\nParrent process pid id:%d ",getpid());
          	printf("\nGrandarrent process pid id:%d ",getppid());   
          	printf("\nArray in descending order: \n");  
          	bubble_dsc(arr,n);
      		  print(arr,n); 	
        }
        else
        {
                printf("\nERROR IN FORK!!!");
        }
	return 0;
}
