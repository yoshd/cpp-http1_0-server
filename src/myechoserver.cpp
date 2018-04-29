#include "httpserver.h"

int main(int argc, char **argv) {
    int sock;
    int status;
    const char *port = argv[1];
    HTTPServer *server = new HTTPServer(port);
    server->start();
    return server->get_status();
}
