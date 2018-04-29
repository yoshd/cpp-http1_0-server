#ifndef INCLUDED_HTTPSERVER_h_
#define INCLUDED_HTTPSERVER_h_
#include "socketmanager.h"

class HTTPServer {
    private:
        SocketManager *socket_manager;
        int status;
    public:
        HTTPServer(const char *port);
        int get_status(void) { return this->status; }
        void start(void);
};

#endif
