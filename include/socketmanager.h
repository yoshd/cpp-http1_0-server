#ifndef INCLUDED_SOCKET_h_
#define INCLUDED_SOCKET_h_

class SocketManager {
    private:
        const char *port;
        int sock;
    public:
        SocketManager(const char *port);
        int get_sock(void) { return this->sock; }
        void s_open(void);
        void s_close(void);
};

#endif
