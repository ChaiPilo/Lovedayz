//throughput=no of process completed per unit time
//cpu utilization=keep the cpu busy as posible (length of completioncycle-idle time)/length pf completion cycle
//tat=CT-AT  interval between time of submission of request to its completion
//response time=ST-AT  time from submission of request to first response
//WT=amount of time process waiting in ready queue. TAT-BT
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process{
	int pId,AT,BT,CT,TAT,WT;
	int rm_BT,ST,RT;
}p[10];
int n;
void getpcb();
void display();
int menu();
void SJFP();
int get_min_burst(int ,int []);
float cal_avgWT();
float cal_avgTAT();
void cal(int);
void RR();
void sortAT();
int main() 
{
	int ch;
	float aWT,aTAT;
    getpcb();
    do
    {
    	ch=menu();
    	switch(ch)
    	{
    		case 1:
    			printf("\n\t\t\t***SJF PREEMPTIVE***");
    			SJFP();
    			display();
    			aWT=cal_avgWT();
    			aTAT=cal_avgTAT();
    			printf("\n\t\tAVERAGE WT  : %.2f",aWT);
				printf("\n\t\tAVERAGE TAT : %.2f",aTAT);
    			break;
    		case 2:
    			printf("\n\t***ROUND ROBIN***");
    			RR();
    			display();
    			aWT=cal_avgWT();
    			aTAT=cal_avgTAT();
    			printf("\n\tAVERAGE WT  : %.2f",aWT);
				printf("\n\tAVERAGE TAT : %.2f",aTAT);
    			break;
    		case 3:
    			printf("\n\tTHANK YOU!!");
    			break;
    		default:
    			printf("\nPlease Enter the correct choice!!");
		}
    	
	}while(ch!=3);
    
   
	return 0;
}

void SJFP()
{
	int i,mb;//minimum burst time 
	int completed=0,current_time=0;
	int iscompleted[n];
	for(i=0;i<n;i++)
	{
		iscompleted[i]=0;
		p[i].rm_BT=p[i].BT;
	}
		
	while(completed!=n)
	{
		//find the process with minimum cpu brust time of each of the n process.
		mb=get_min_burst(current_time,iscompleted);
		
		if(mb!=-1)//found
		{
			if(p[mb].rm_BT==p[mb].BT)
			   p[mb].ST=current_time;
			p[mb].rm_BT-=1;
			current_time++;
			if(p[mb].rm_BT==0)  //if process completed then calculate
			{
				p[mb].CT=current_time;
			    cal(mb);
				completed++;
				iscompleted[mb]=1;
			}
	    }
	    else //this when cpu is idle
	    {
	    	current_time++;
		}
	}
}

int get_min_burst(int current_time,int iscompleted[])
{
	int i,min=INT_MAX,mb=-1;
	for(i=0;i<n;i++)
	{
		if(p[i].AT<=current_time && iscompleted[i]==0)
		{
			if(p[i].rm_BT<min)
			{
				min=p[i].rm_BT;
				mb=i;
			}
			if(p[i].rm_BT==min)
			{
				if(p[i].AT<p[mb].AT)
				{
					min=p[i].rm_BT;
					mb=i;
				}
			}
		}
	}
	return mb;
}
void getpcb()
{
	int i;
	printf("\n\tEnter details of PCB");
	printf("\n\tEnter Total no of process: ");
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		printf("\tEnter process P%d Arrival time and Burst Time: ",i);
		scanf("%d",&p[i].AT);
		scanf("%d",&p[i].BT);
	//	p[i].rm_BT=p[i].BT;
		p[i].pId=i;
	}
}

void display()
{
	int i;
	printf("\n\t\t*****************PCB******************");
	printf("\n\tPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT");
	for(i=0;i<n;i++)
	{
		printf("\n\tP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",p[i].pId,p[i].AT,p[i].BT,p[i].ST,p[i].CT,p[i].TAT,p[i].WT,p[i].RT);
	}
}

int menu()
{
	int ch;
	printf("\n\t\t****MENU*****");
	printf("\n\t\t1. SJF P");
	printf("\n\t\t2. RR");
	printf("\n\t\t3. EXIT");
	printf("\n\t\tEnter Choice: \t");
	scanf("%d", &ch);
	return ch;
}

float cal_avgWT()
{
	int sum=0,i;
	float avg;
	for(i=0;i<n;i++)
	   sum+=p[i].WT;
	   
	avg=(float)sum/n;
	return avg;
}

float cal_avgTAT()
{
	int sum=0,i;
	float avg;
	for(i=0;i<n;i++)
	   sum+=p[i].TAT;
	   
	avg=(float)sum/n;
	return avg;
}

void cal(int mb) //minimum burst index
{
		p[mb].TAT=p[mb].CT-p[mb].AT;
		p[mb].WT=p[mb].TAT-p[mb].BT;
		p[mb].RT=p[mb].ST-p[mb].AT;
}

void sortAT()
{
	struct process temp;
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(p[j].AT>p[j+1].AT)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}
}
void RR()
{
	int tq,j;
	printf("\nEnter time quantum: ");
	scanf("%d",&tq);
	sortAT();
	for(j=0;j<n;j++)
	{
		p[j].rm_BT=p[j].BT;
		p[j].ST=0;
	}
	int completed=0,current_time=0,i=0,flag=0;
	printf("\nGANT CHART\n");
	printf("0");
	while(completed!=n)
	{
		if(p[i].rm_BT<=tq && p[i].rm_BT>0)
		{
			if(p[i].rm_BT==p[i].BT )  //only once per process
			    p[i].ST=current_time;
			current_time+=p[i].rm_BT;
			printf("->P%d<- %d",p[i].pId,current_time);
			p[i].rm_BT=0;
			flag=1; //means process completed
		}
		else if(p[i].rm_BT > 0)
		{
			if(p[i].rm_BT==p[i].BT)  //only once per process
			    p[i].ST=current_time;
			p[i].rm_BT-=tq;
			current_time+=tq;
			printf("->P%d<- %d",p[i].pId,current_time);
		}
		if(p[i].rm_BT==0 && flag==1)
		{
			p[i].CT=current_time;
			completed++;
			cal(i);
			flag=0;
		}
		if(i==n-1)
		   i=0;
		else if(p[i+1].AT <= current_time)
		   i++;
		else
		   i=0;
	}
}

