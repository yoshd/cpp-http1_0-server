#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include "socketmanager.h"

SocketManager::SocketManager(const char *port) {
    this->port = port;
    this->sock = -1;
}

void SocketManager::s_open(void) {

    struct addrinfo hints;
    struct addrinfo *addr_set;
    struct addrinfo *addr;
    int error_code;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error_code = getaddrinfo(NULL, this->port, &hints, &addr_set);
    if (error_code != 0) {
        perror("getaddrinfo");
    }

    for (addr = addr_set; addr; addr = addr->ai_next) {
        this->sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (this->sock < 0) {
            perror("socket");
            continue;
        }

        if (bind(this->sock, addr->ai_addr, addr->ai_addrlen) != 0) {
            perror("bind");
            close(this->sock);
            this->sock = -1;
            continue;
        }

        if (listen(sock, SOMAXCONN) != 0) {
            perror("listen");
            close(sock);
            this->sock = -1;
            continue;
        }
        break;
    }
}

void SocketManager::s_close(void) {
    close(this->sock);
}
