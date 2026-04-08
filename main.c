#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <err.h>


int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sfd == -1)
    {
	printf("Opening new socket failed.\n");
	exit(1);
    }
    printf("open fd: %d\n", sfd);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 8080;
    inet_pton(AF_INET, "172.30.1.45", &(addr.sin_addr));

    if (bind(sfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
    {
	printf("failed to bind.\n");
    }

    if (listen(sfd, 1) == -1)
    {
	printf("failed to start listening.");
    }

    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size = sizeof(peer_addr);
    int cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    
    if (cfd == -1)
    {
	err(EXIT_FAILURE, "Accept");
    }

    return 0;
}
