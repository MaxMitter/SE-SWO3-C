#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define BACKLOG 3

int main(int argc, char const *argv[])
{
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo, *rp;
    int socket_nr, backlog, client_socket;
    struct sockaddr client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char* port = argv[1];

    printf("Selected port: %s\n", port);

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
        serve(client_socket);
        close(client_socket);
    }
    return 0;
}
