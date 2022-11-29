#include<stdio.h>
#include<stdlib.h>
void FIFO(int[],int[],int,int);
void LRU(int[],int[],int,int);
void OPTIMAL(int[],int[],int,int);
int main()
{
	int i,ch,l,f;
	printf("\nEnter the length of string: ");
	scanf("%d",&l);
	printf("\nEnter No of page Frame: ");
	scanf("%d",&f);
	int S[l],F[f];
	printf("\nEnter The reference string: ");
	for(i=0;i<l;i++)
	   scanf("%d",&S[i]);
	while(1)
	{
		for(i=0;i<f;i++)
	        F[i]=-1;
	    printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1:FIFO\n\n\t2:LRU\n\n\t3:OPT\n\n\t4:EXIT");
        printf("\n\n\tEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
        	case 1:
        	 	FIFO(S,F,l,f);
        		break;
        	case 2:
        		LRU(S,F,l,f);
        		break;
        	case 3:
        		OPTIMAL(S,F,l,f);
        		break;
        	case 4:
        		printf("\nTHANK YOU!!");
        		return 0;
        	default:
        		printf("\nPlease Enter the correct choice");
		}
	}
}

void FIFO(int S[],int F[],int l,int f)
{
	printf("\n\tPAGE\t\tFRAMES\t\t\tFAULT");
	int i,j,flag=0,k=0,cnt=0;
	for(i=0;i<l;i++)
	{
		//check string is present or not;
		for(j=0;j<f;j++)
		{
			if(S[i]==F[j])
			   { 
			       flag=1;   //present
			       break;  
		       }
		}
			
		if(flag==0)// not present
		{
			printf("\n\t%d",S[i]);
			F[k]=S[i];
			k++;
			
			//printf page fault table
			for(j=0;j<f;j++)
			{
			if(F[j]==-1)
			    printf("\t-");
			else
			    printf("\t%d",F[j]);
			}
			printf("\t%C",'F');
			cnt++;
		}
		else//present
		{
			flag=0;
			printf("\n\t%d",S[i]);
			for(j=0;j<f;j++)
			{
				if(F[j]==-1)
			       printf("\t-");
			    else
			       printf("\t%d",F[j]);
			}
			printf("\t%C",'H');
		}
		if(k==f)
		  k=0;
	}
	
	printf("\nNo of page fault %d",cnt);
	printf("\nNo of page Hint %d",l-cnt);
}

void LRU(int S[],int F[],int l,int f)
{
	printf("\n\tPAGE\t\tFRAMES\t\tFAULT");
	int i,j,k=0,cnt=0,flag=0,T=0,m;
	for(i=0;i<l;i++)
	{
		printf("\n\t%d",S[i]);
		for(j=0;j<f;j++)
		{
			if(F[j]==S[i])  //check found or not
			{
				flag=1;
				break;
			}
		}
		
		if(k!=f && flag==0)  //this for first f page fault
		{
			F[T]=S[i];
			k++;
			if(k!=f)
			    T++;
		}
		else
		{
			if(flag==0)
			{
				for(j=0;j<T;j++)
				{
					F[j]=F[j+1];
				}
				F[T]=S[i];
			}
			if(flag==1)
			{
				for(m=j;m<T;m++)
				{
					F[m]=F[m+1];
				}
				F[T]=S[i];
			}
		}
		for(j=0;j<f;j++)
		{
			if(F[j]==-1)
			    printf("\t-");
			else
			    printf("\t%d",F[j]);
		}
		if(flag==0)
		{
			printf("\t%C",'F');
			cnt++;
		}
		else
		    printf("\t%C",'H');
		flag=0;
	}
	printf("\nNo of page fault %d",cnt);
	printf("\nNo of page Hint %d",l-cnt);
}

void OPTIMAL(int S[],int F[],int l,int f)
{
	printf("\n\tPAGE\t\tFRAMES\t\tFAULT");
   int i,j=0,k,m,flag=0,cnt=0,temp[10];
   for(i=0;i<10;i++)
     temp[i]=0; 
     
   for(i=0;i<l;i++) 
    {
       for(k=0;k<f;k++)
        {
          if(F[k]==S[i])
            flag=1;
        }
  
       if(j!=f && flag==0)
        {         
          F[j]=S[i];   
          j++;
        }
 
       else if(flag==0)    
        {
           for(m=0;m<f;m++)
            {
              for(k=i+1;k<l;k++)
               {
                  if(F[m]!=S[k])
                   {   
                     temp[m]=temp[m]+1;
                   }
                  else
                   break;
               }
            }
           m=0;
           for(k=0;k<f;k++)
            {              
               if(temp[k]>temp[m])
                {
                  m=k;
                }
            }

           F[m]=S[i];
        }

       printf("\n\t%d",S[i]);
       for(k=0;k<f;k++)
        {
        	if(F[k]==-1)
        	   printf("\t-");
        	else
               printf("\t%d",F[k]);
        }
       if(flag==0)
        {
          printf("\t%C",'F');
          cnt++;
        }  
       else
         printf("\t%C",'H');
       flag=0;

       for(k=0;k<10;k++)
         temp[k]=0; 
     }
    printf("\nNo of page fault %d",cnt);
	printf("\nNo of page Hint %d",l-cnt);
}    

