/*Assignment no. 8
Inter-process Communication using Shared Memory using System V. Application to
demonstrate: Client and Server Programs in which server process creates a shared memory segment and writes the message to the shared memory segment. Client process reads the message from the shared memory segment and displays it to the screen.

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SZ 4096

int main(){
	
	int shm_id;
	//key_t mykey;
	int *shm_ptr;
	int data,ret_val;
	int read_data;
	int pid;
	shm_id=shmget( IPC_PRIVATE , SZ , IPC_CREAT | 0666 );
	if(shm_id<0){
		printf("\n ERROR at adressing ,memory\n");
	}
	else{
		printf("Shared memo is created\n");
		printf("shared memory id  %d\n",shm_id);
		
		shm_ptr=(int*) shmat(shm_id,NULL,0);
			if((int) shm_ptr!=-1){
				printf("\nSHARED MEMORY IS ATTACHED TO \t%d\n",shm_ptr);
			}
			printf("\nENTER THE DATA\n");
			scanf("%d",&data);
			*shm_ptr = data;
			
			
		pid=fork();
		if(pid==0){
			
			
			if((int) shm_ptr!=-1){
			printf("\nSHARED MEMORY IS ATTACHED TO \t%d\n",shm_ptr);
			read_data=*shm_ptr;
			printf("data from shared memory \t %d",*shm_ptr);
		}
		}
		ret_val =shmdt((void *)shm_ptr);
		if(ret_val==0){
				printf("\n shared memory is sucessfully detached\n");
			}
			else{
				printf("shmdt srror");
			}
	}
return 0;
}


/*



student@student-OptiPlex-390:~/Desktop/s$ ./a.out
Shared memo is created
shared memory id  1966093

SHARED MEMORY IS ATTACHED TO 	504512512

ENTER THE DATA
5236

 shared memory is sucessfully d4etached

SHARED MEMORY IS ATTACHED TO 	504512512
data from shared memory 	 5236
 shared memory is sucessfully d4etached
*/
