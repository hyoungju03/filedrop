#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>


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

    struct sockaddr_in6 sock_addr;
    sock_addr.sin6_family = AF_INET6;
    sock_addr.sin6_port = htons(8080);
    sock_addr.sin6_scope_id = if_nametoindex(if_name);
    // printf("sock_addr size: %zu (B)\n", sizeof(sock_addr));

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

    if (listen(sfd, 1) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    };

    struct sockaddr_in6 peer_sock_addr;
    peer_sock_addr.sin6_family = AF_INET6;
    peer_sock_addr.sin6_port = htons(48724);
    peer_sock_addr.sin6_scope_id = if_nametoindex(if_name);

    socklen_t peer_addr_size = sizeof(peer_sock_addr);
    int cfd = accept(sfd, (struct sockaddr *) &peer_sock_addr, &peer_addr_size);
    if (cfd == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    size_t read_byte = 38;
    char buf[read_byte];

    size_t act_read = read(cfd, buf, read_byte); 
    printf("Read string: %s\n", buf);

    return 0;
}

