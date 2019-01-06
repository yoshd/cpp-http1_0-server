#include "httpserver.h"

int main(int argc, char **argv) {
    const char *port = argv[1];
    HTTPServer *server = new HTTPServer(port);
    server->start();
    return server->get_status();
}
