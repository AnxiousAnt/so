#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#define SEGSIZE 100
int main(int argc, char *argv[ ])
{int shmid,cntr;
key_t key;
char *segptr;
char buff[]="poooda......";
key=ftok(".",'s');
if((shmid=shmget(key, SEGSIZE, IPC_CREAT | IPC_EXCL | 0666))== -1)
{
if((shmid=shmget(key,SEGSIZE,0))==-1)
{
perror("shmget");
exit(1);
}
}
else
{
printf("Creating a new shared memory seg \n");
printf("SHMID:%d",shmid);
}
system("ipcs –m");
if((segptr=(char*)shmat(shmid,0,0))==(char*)-1)
{
perror("shmat");
exit(1);
}
printf("Writing data to shared memory...\n");
strcpy(segptr,buff);
printf("DONE\n");
printf("Reading data from shared memory...\n");
printf("DATA:-%s\n",segptr);
printf("DONE\n");printf("Removing shared memory Segment...\n");
if(shmctl(shmid,IPC_RMID,0)== -1)
printf("Can‟t Remove Shared memory Segment...\n");
else
printf("Removed Successfully");
}







//Writer process

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	//r-4 w-2 x-1
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char str = (char) shmat(shmid,(void*)0,0);

	printf("Write Data : ");
	gets(str);

	printf("Data written in memory: %s\n",str);
	
	//detach from shared memory
	shmdt(str);

	return 0;
}

//Reader process
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char str = (char) shmat(shmid,(void*)0,0);

	printf("Data read from memory: %s\n",str);
	
	//detach from shared memory
	shmdt(str);
	
	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}
