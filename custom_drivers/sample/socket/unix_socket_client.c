#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/un.h>

int main()
{
	char str1[] = "message from client\n";
	int socket_fd1;
	struct sockaddr_un unix_addr;
	
	unix_addr.sun_family = AF_UNIX;
	strcpy(unix_addr.sun_path,"./socket1");

	// opening a UNIX socket, with DGRAM type protocol
	socket_fd1 = socket(AF_UNIX, SOCK_DGRAM, 0);
	
	//sending first message
	sendto(socket_fd1, str1, strlen(str1)+1,0,(struct sockaddr*)&unix_addr, sizeof(unix_addr));

	sleep(2);
	
	//socket will be closed.
	close(socket_fd1);

}
