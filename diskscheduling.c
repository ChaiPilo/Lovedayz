#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void SSTF();
void SCAN();
void CLOOK();
void sort(int[],int);
void display(int,int,int[]);
int main()
{
	int ch,YN;
	do
	{
 		printf("\n\n\t*********** MENU ***********"); 
		printf("\n\n\t1:SSTF\n\n\t2:SCAN\n\n\t3:CLOOK\n\n\t4:EXIT"); 
		printf("\n\n\tEnter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1:
				SSTF();
				break;
			case 2:
				SCAN();
				break;
			case 3:
				CLOOK();
				break;
			case 4:
			        printf("THANK YOU");
				exit(0);
				break;
			default:
				printf("\n Please Enter Correct choice!!!");
		
		}
		printf("\n\n\tDo u want to continue IF YES PRESS 1\n\n\tIF NO PRESS 0: ");
		scanf("%d", &YN); 	
	}while(YN==1);

	return 0;
}

void SSTF()
{
	int i,n,initial,TotalHeadMovement=0,d,index;
	printf("\nEnter No of request: ");
	scanf("%d",&n);
	int RQ[n];//request queue
	int SS[n];//seek sequence
	int visited[n];
	for(i=0;i<n;i++)
	    visited[i]=0;
	printf("\nEnter the requests in sequence: ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&RQ[i]);
	}
	printf("\nEnter Initial Head Position: ");
	scanf("%d",&initial);
	int count=0,k=0;
    while(count != n)
    {
    	int min=INT_MAX;
    	for(i=0;i<n;i++)
    	{
    		if(visited[i]==1)
    		    continue;
    		else
    		d=abs(RQ[i]-initial);
    		if(d<min)
    		{
    			min=d;
    			index=i;
			}
		}
		TotalHeadMovement+=min;
		initial=RQ[index];
		SS[k++]=RQ[index];
	//	RQ[index]=INT_MAX;
		visited[index]=1;
		
		count++;
	}
    //total_head_movement=applySSTF(RQ,initial,)
	display(TotalHeadMovement,n,SS);
}

void SCAN()
{
	int i,j,n,initial,TotalHeadMovement=0,d,index,size,move,temp,k=0;
	printf("\nEnter No of request: ");
	scanf("%d",&n);
	int RQ[n];//request queue
	int SS[n+1];//seek sequence
	int visited[n];
	for(i=0;i<n;i++)
	    visited[i]=0;
	printf("\nEnter the requests in sequence: ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&RQ[i]);
	}
	printf("\nEnter Initial Head Position: ");
	scanf("%d",&initial);
	printf("\nEnter Total Disk Size: ");
	scanf("%d",&size);
	printf("\nEnter head movement dorection 1 for high and 0 for low : ");
	scanf("%d", &move);
	
	//sorting request queue in asccending order:
	sort(RQ,n);
	
	for(i=0;i<n;i++)
	{
		if(initial < RQ[i])
		{
			index=i;
			break;
		}
	}
	
	if(move==1)
	{
		for(i=index;i<n;i++)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
		TotalHeadMovement+=(size-RQ[i-1]-1);
		initial=size-1;
		SS[k++]=size-1;
		for(i=index-1;i>=0;i--)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
	}
	else
	{
		for(i=index-1;i>=0;i--)
		{
			TotalHeadMovement+=abs(initial-RQ[i]);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
		TotalHeadMovement+=abs(initial-0);
		initial=0;
		SS[k++]=0;
		for(i=index;i<n;i++)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
	}
    display(TotalHeadMovement,n,SS);
	
}

void CLOOK()
{
	int n,i,initial,move,TotalHeadMovement=0,k=0;
	printf("\nEnter total no of request: ");
	scanf("%d",&n);
	int RQ[n],SS[n];
	printf("\nEnter the Request in sequence: ");
	for(i=0;i<n;i++)
	    scanf("%d",&RQ[i]);
	printf("\nEnter Initial Head Position: ");
	scanf("%d",&initial);
	printf("\nEnter head movement dorection 1 for high and 0 for low : ");
	scanf("%d",&move);
	
	sort(RQ,n);
	int index;
	for(i=0;i<n;i++)
	{
		if(initial<RQ[i])
		{
			index=i;
			break;
		}
	}
	
	if(move==1)
	{
		for(i=index;i<n;i++)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
		for(i=0;i<index;i++)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
	}
	else
	{
		for(i=index-1;i>=0;i--)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
		for(i=n-1;i>=index;i--)
		{
			TotalHeadMovement+=abs(RQ[i]-initial);
			initial=RQ[i];
			SS[k++]=RQ[i];
		}
		
	}

	display(TotalHeadMovement,n,SS);
	
}

void sort(int RQ[],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(RQ[j]>RQ[j+1])
			{
				temp=RQ[j];
				RQ[j]=RQ[j+1];
				RQ[j+1]=temp;
			}
		}
	}
}

void display(int TotalHeadMovement,int n,int SS[])
{
	int i;
		float avg=(float)TotalHeadMovement/n;
	printf("\nTotal Head Movement: %d ",TotalHeadMovement);
	printf("\nAverage SEEK_TIME: %.2f",avg);
	printf("\nSeek sequence is: ");
	for(i=0;i<n;i++)
	   printf("%d ",SS[i]);
	
}
