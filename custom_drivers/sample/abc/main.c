#include <stdio.h>
#include "my_lib.h"

int main()
{
	int loop_1;
	
	for(loop_1=0; loop_1 <= 12; loop_1 ++)
	{
	printf("return value is: %d \n",fun_call(1,0,10));


	printf("return value is: %d \n",fun_call(1,1,10));
	}
}
