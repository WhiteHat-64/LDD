#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int i;
  unsigned char* ptr;
  ptr = malloc(100);
  printf("%p\n",ptr);
  for(i=0;i=1000000;i++)
  {
  printf("%p,  %c\n",ptr++,*ptr);
	  
  }
}
