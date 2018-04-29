#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include "socketmanager.h"
#include "httpserver.h"
#include "httpprocessor.h"

static int _interrupted = 0;

void sigint_action(int signum)
{
    _interrupted = 1;
}

HTTPServer::HTTPServer(const char *port) {
    this->socket_manager = new SocketManager(port);
    this->status = -1;
}

void HTTPServer::start(void) {

    this->socket_manager->s_open();
    int accept_socket = socket_manager->get_sock();

    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = sigint_action;
    action.sa_flags = SA_RESETHAND;

    if (sigaction(SIGINT, &action, NULL) != 0) {
        perror("sigaction");
        this->status = -1;
    }

    memset(&action, 0, sizeof(action));
    action.sa_handler = SIG_IGN;
    action.sa_flags = SA_NOCLDWAIT;
    if (sigaction(SIGCHLD, &action, NULL) != 0) {
        perror("sigaction");
        this->status = -1;
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
        this->socket_manager->s_close();
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

    this->status = 0;
}
