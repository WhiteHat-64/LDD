#include <unistd.h>
#include <stdio.h>


int main()

{

	printf("Before execve...\n");

	if(execve("dummy",NULL,NULL))
	printf("execve failed\n");	

	printf("after execve...\n");

	return 0;
}
