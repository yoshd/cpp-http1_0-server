#ifndef INCLUDED_HTTPRequestReader_h_
#define INCLUDED_HTTPRequestReader_h_
#include <string>
#include <sys/socket.h>
#include <poll.h>

class HTTPRequestReader {
    private:
        std::string request_str;
        int sock;
        struct pollfd read_fd;
    public:
        HTTPRequestReader(int sock);
        void read_request(void);
        std::string get_request_str(void) { return this->request_str; }
};

#endif
