#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKLOG 3


char* get_ip_str(const struct sockaddr* sa, char* s, size_t maxlen){
    switch (sa->sa_family)
    {
    case AF_INET:
        inet_ntop(AF_INET, &(((struct sockaddr_in*)sa)->sin_addr), s, maxlen);
        break;
    case AF_INET6:
        inet_ntop(AF_INET6, &(((struct sockaddr_in6*)sa)->sin6_addr), s, maxlen);
        break;
    default:
        strncpy(s, "Unknown AF", maxlen);
        break;
    }

    return s;
}

int get_port(const struct sockaddr* sa){
    int port = 0;
    switch (sa->sa_family)
    {
    case AF_INET:
        port = ntohs(((struct sockaddr_in*)sa)->sin_port);
        break;
    case AF_INET6:
        port = ntohs(((struct sockaddr_in6*)sa)->sin6_port);
        break;
    default:
        break;
    }

    return port;
}

int main(int argc, char const *argv[])
{
    int status;
    char* port = argv[1];
    struct addrinfo hints;
    struct addrinfo *servinfo, *rp;
    int socket_nr, backlog, client_socket;
    struct sockaddr client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    printf("Selected Port: %s\n", port);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    for (rp = servinfo; rp != NULL; rp = rp->ai_next) {
        socket_nr = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (socket_nr == -1)
            continue;
        
        int enable = 1;
        status = setsockopt(socket_nr, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
        if (status < 0) {
            fprintf(stderr, "SetSockOpt failed: %s\n", gai_strerror(status));
            exit(1);
        }

        if (bind(socket_nr, rp->ai_addr, rp->ai_addrlen) == 0)
            break;
            
        close(socket_nr);
    }

    if (rp == NULL) {
        fprintf(stderr, "Could not bind\n");
        exit(1);
    }

    freeaddrinfo(servinfo);

    printf("Server bound to socket %d\n", socket_nr);

    if (listen(socket_nr, BACKLOG) == -1) {
        printf("Error while listening");
    }

    while (1) {
        printf("Waiting for connection...\n");
        client_socket = accept(socket_nr, &client_addr, &client_addr_len);
        if (client_socket == -1) {
            fprintf(stderr, "Client socket invalid: %s\n", gai_strerror(client_socket));
            exit(1);
        }
        char client_addr_str[client_addr_len];
        get_ip_str(&client_addr, client_addr_str, client_addr_len);
        int client_port = get_port(&client_addr);
        printf("Client IP: %s:%d\n", client_addr_str, client_port);
        serve(client_socket);
        close(client_socket);
    }
    return 0;
}