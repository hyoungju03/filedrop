#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>

#define SERVER_PORT 8080 

char *ipv6_addr = "fe80::101b:6c28:18f4:48a6";
char *if_name = "en0";


int main(int argc, char *argv[])
{
    // check localhost setting
    int opt;
    while ((opt = getopt(argc, argv, "l")) != -1)
    {
        if (opt == 'l')
        {
            ipv6_addr = "::1";
            if_name = "lo";
        }
    }

    int sfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(SERVER_PORT);
    server_addr.sin6_scope_id = if_nametoindex(if_name);

    if (inet_pton(AF_INET6, ipv6_addr, &(server_addr.sin6_addr)) == 1)
    {
        // printf("inet_pton success\n");
    }

    const char *msg = "First real networking program I wrote!";

    if (connect(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
   
    ssize_t bytes_sent = send(sfd, msg, strlen(msg), 0);

    printf("Bytes sent: %zd (B)\n", bytes_sent);

    return 0;
}
