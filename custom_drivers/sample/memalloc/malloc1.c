#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n,i,j,temp;
	printf("n: ");
	scanf("%d",&n);
	temp = sizeof(int)*n*3;

	int (*ptr)[n][3] = (int (*)[n][3]) malloc(temp);

	if(ptr==NULL)
	{
		printf("No memory\n");
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%d",&(*ptr)[i][j]);
		}
	}

	printf("\n");
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d ",(*ptr)[i][j]);
		}
	printf("\n");
	}

	free(ptr);

}
