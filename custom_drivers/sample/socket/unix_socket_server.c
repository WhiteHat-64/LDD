#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
	int socket_fd1;
	struct sockaddr_un unix_addr;
	socklen_t length;

	char str1[200];
	
	unix_addr.sun_family = AF_UNIX;
	strcpy(unix_addr.sun_path,"./socket1");

	// opening a UNIX socket, with DGRAM type protocol
	socket_fd1 = socket(AF_UNIX, SOCK_DGRAM, 0);
	
	//binding with 'socket1' socket file.
	bind(socket_fd1,(struct sockaddr*) &unix_addr, sizeof(unix_addr));

	//sending first message
	recvfrom(socket_fd1, str1, 100,0,(struct sockaddr*)&unix_addr,&length);

	printf("%s\n",str1);

	//socket will be closed.
	close(socket_fd1);

}
