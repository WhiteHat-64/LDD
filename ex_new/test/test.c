#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	int fd;
	off_t offset;
	size_t size;
	unsigned char buff[100]="";

	fd = open(argv[1],O_RDWR);
	perror("open");
	size = read(fd, buff,50);
	perror("read1");
	
	offset = lseek(fd,0,SEEK_CUR);
	perror("lseek1");
	printf("offset beofre writing is %ld\n",offset);
		
	printf("app buffer address %p\n %s\n", buff, buff);
	size = write(fd, "manipulating the existing data\n",33);
	perror("write");

	offset = lseek(fd,0,SEEK_CUR);
	perror("lseek2");
	printf("offset beofre writing is %ld\n",offset);
	
	printf("data written into the disc is %lu\n",size);
	size = read(fd, buff,50);
	perror("after writing read2");

	offset = lseek(fd,0,SEEK_CUR);
	perror("lseek3");
	printf("offset beofre writing is %ld\n",offset);

	sleep(30);

	printf("app buffer address %p\n %s\n", buff, buff);
	close(fd);
	return 0;
}
