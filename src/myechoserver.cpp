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
#include "httpresponse.h"
#include "httprequestreader.h"
#include "httprequestparser.h"
#include "httprequest.h"
#include "httpresponsewriter.h"

#define BUFFER_SIZE 512
#define READ_TIMEOUT 10000

int open_socket(const char *service) {

    struct addrinfo hints;
    struct addrinfo *addr_set;
    struct addrinfo *addr;
    int error_code;
    int sock = -1;
    int on = 1;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error_code = getaddrinfo(NULL, service, &hints, &addr_set);
    if (error_code != 0) {
        return -1;
    }

    for (addr = addr_set; addr; addr = addr->ai_next) {
        sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (sock < 0) {
            perror("socket");
            continue;
        }

        if (bind(sock, addr->ai_addr, addr->ai_addrlen) != 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }

        if (listen(sock, SOMAXCONN) != 0) {
            perror("listen");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }

    return sock;
}

int run(int sock) {

    HTTPRequestReader *hrr = new HTTPRequestReader(sock);
    hrr->read_request();
    std::cout << hrr->get_request_str() << std::endl;
    std::string body = "<h1>Your request dump</h1>\r\n" + hrr->get_request_str() + "\r\n";

    HTTPRequest* req = HTTPRequestParser::parse(hrr->get_request_str());

    HTTPResponse *hr = new HTTPResponse();
    hr->set_body(body);
    hr->set_status_code(200);

    HTTPResponseWriter *hrw = new HTTPResponseWriter(sock);
    hrw->write_response(hr);
}

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
            status = run(connection_socket);
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
    sock = open_socket(argv[1]);
    status = start_server(sock);
    close(sock);
    return status;
}
