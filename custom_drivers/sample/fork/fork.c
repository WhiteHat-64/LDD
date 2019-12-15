#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	pid_t pid;

	printf("%d: before fork\n",getpid());
	pid = fork();
	printf("%d: after fork\n",getpid());
	
	if(pid>0)
	{
		printf("%d: Parent process\n",getpid());
	}
	else if(pid==0)
	{
		printf("%d: child process\n", getpid());
		if(execve("dummy_",NULL,NULL))
		printf("%d: Error execve\n",getpid());
	}
	else
	{
		printf("%d: fork failed...\n",getpid());
	}

}
