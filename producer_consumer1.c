#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/syscall.h>

void* producer();
void* consumer();

struct Shared{
    int buff[20];
    sem_t full,empty;
}sh;

int in=0,out=0;
sem_t mutex;
int item;
int main()
{
   pthread_t ptid1,ptid2,ctid1;
   sem_init(&sh.empty,0,20);
   sem_init(&sh.full,0,0);
   sem_init(&mutex,0,1);
      
   pthread_create(&ptid1,NULL,producer,NULL);
   pthread_create(&ptid2,NULL,producer,NULL);
   pthread_create(&ctid1,NULL,consumer,NULL);
   
   pthread_join(ptid1,NULL);
   pthread_join(ctid1,NULL);
   
   return 0;
}

void* producer()
{
   int ptid;
   while(1)
   {
      
	      item=in;
	      sem_wait(&sh.empty);
	      sem_wait(&mutex);
	      
	      sh.buff[in++]=item;
	      printf("\n(producer) %d is a id of item %d",syscall(SYS_gettid,ptid),item);
	      sem_post(&mutex);      
	      sem_post(&sh.full);
	      sleep(2);
   }

}

void* consumer()
{
   int ctid;
   while(1)
   {
      while(out<=in)
      {
 //        item=in;
         sem_wait(&sh.full);
         sem_wait(&mutex);
      
         item=sh.buff[out++];
         printf("\n(consumer) %d is a id of item %d",syscall(SYS_gettid,ctid),item);
         sem_post(&mutex);      
         sem_post(&sh.empty);
         sleep(2);
      }
   }

}

