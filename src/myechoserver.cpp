#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include "httpprocessor.h"
#include "socketmanager.h"

#define BUFFER_SIZE 512
#define READ_TIMEOUT 10000

static int _interrupted = 0;

void sigint_action(int signum)
{
    _interrupted = 1;
    return;
}

int start_server(int accept_socket) {
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = sigint_action;
    action.sa_flags = SA_RESETHAND;

    if (sigaction(SIGINT, &action, NULL) != 0) {
        perror("sigaction");
        return -1;
    }

    memset(&action, 0, sizeof(action));
    action.sa_handler = SIG_IGN;
    action.sa_flags = SA_NOCLDWAIT;
    if (sigaction(SIGCHLD, &action, NULL) != 0) {
        perror("sigaction");
        return -1;
    }

    while (!_interrupted) {
        struct sockaddr_storage addr;
        socklen_t addrlen;
        int connection_socket;
        pid_t pid;

        addrlen = sizeof(addr);

        connection_socket = accept(accept_socket, (struct sockaddr*)&addr,
                &addrlen);
        if (connection_socket < 0) {
            if (errno == EINTR) { 
                continue;
            }
            perror("accept");
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            close(connection_socket);
            break;
        } else if (pid == 0) {
            int status;
            close(accept_socket);
            status = HTTPProcessor::run(connection_socket);
            exit(status);
        }
        close(connection_socket);
    }

    if (_interrupted) {
        printf("Interrupted.\n");
    }

    memset(&action, 0, sizeof(action));
    action.sa_handler = SIG_IGN;
    action.sa_flags = SA_RESETHAND;
    if (sigaction(SIGTERM, &action, NULL) != 0) {
        perror("sigaction");
    }
    if (killpg(0, SIGTERM) != 0) {
        perror("killpg");
    }

    return 0;
}

int main(int argc, char **argv) {
    int sock;
    int status;
    SocketManager *socket_manager = new SocketManager(argv[1]);
    socket_manager->s_open();
    sock = socket_manager->get_sock();
    status = start_server(sock);
    close(sock);
    return status;
}
