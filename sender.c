#include <stdio.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <net/if.h>


int main()
{
    
    int sfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 sock_addr;
    sock_addr.sin6_family = AF_INET6;
    sock_addr.sin6_port = htons(8080);
    sock_addr.sin6_scope_id = if_nametoindex("en0");

    // printf("sock_addr size: %zu (B)\n", sizeof(sock_addr));

    const char *ipv6_addr = "fe80::101b:6c28:18f4:48a6";
    
    if (inet_pton(AF_INET6, ipv6_addr, &(sock_addr.sin6_addr)) == 1)
    {
        // printf("inet_pton success\n");
    }

    // printf("sin6_addr size: %zu (B)\n", sizeof(sock_addr.sin6_addr));
    fflush(stdout);

    if (bind(sfd, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return 0;
}
