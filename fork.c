#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int pid, pid1, pid2;
	pid = fork();
	
	if (pid == -1)
	{
		printf("ERROR IN PROCESS CREATION\n");
		exit(1);
	}
	
	if(pid != 0)
	{
		pid1 = getpid();
		printf("\nTHE PARENT PROCESS ID IS %d\n", pid1); 
	}
	
	else
	{
		pid2 = getpid();
		printf("\nTHE CHILD PROCESS ID IS %d\n", pid2);
	}
	return 0;
}
