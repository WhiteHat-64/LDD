#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	ssize_t no_bytes;
	unsigned char buff[101];
	unsigned char buff1[100]="Sample data from userspace";
	int fd;
	fd = open("/dev/my_device",O_RDONLY);
	printf("fd = %d\n",fd);
	
	no_bytes = read(fd,buff,100);
	printf("number of bytes read = %ld\n", no_bytes);
	

	buff[100]=0;
	printf("%s\n",buff);
	close(fd);
}
