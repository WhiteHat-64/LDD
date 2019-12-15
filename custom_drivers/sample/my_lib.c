#include "my_lib.h"


int fun_call(int input_flag, int reset_flag, int max_counter)
{
	static counter = 0;

	if((input_flag == 1) && (reset_flag == 0))
	{
		counter = counter + 1;
	}

	else if (reset_flag == 1)
	{
		counter = 0;
	}
	else
	{}

	if(input_flag == 1 && max_counter == counter)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


