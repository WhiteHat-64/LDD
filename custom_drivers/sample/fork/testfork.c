#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv)
{
	pid_t pid1,pid2;
	int i;

	printf("before fork() pid is %d, ppid is %d\n",getpid(),getppid());
	pid1 = fork();
	pid2 = fork();
	pid2 = fork();
	pid2 = fork();
	pid2 = fork();
	
	//for(i=0;i<10;i++)
	{
	printf("after fork() pid is %d, ppid is %d\n",getpid(),getppid());
	//printf("return value of fork is %d\n",pid);
	}
	return 0;
}
