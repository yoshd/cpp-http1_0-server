#include <string>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include "httprequestreader.h"

#define BUFFER_SIZE 1024
#define READ_TIMEOUT 10000

HTTPRequestReader::HTTPRequestReader(int sock) {
    this->request_str = "";
    this->sock = sock;

    memset(&this->read_fd, 0, sizeof(this->read_fd));

    this->read_fd.fd = this->sock;
    this->read_fd.events = POLLIN;
}

void HTTPRequestReader::read_request(void) {
    int poll_count;
    poll_count = poll(&this->read_fd, 1, READ_TIMEOUT);

    if (poll_count <= 0) {
        close(this->sock);
    }

    char buf[BUFFER_SIZE];
    ssize_t read_len;
    read_len = read(this->sock, buf, BUFFER_SIZE);

    if (read_len <= 0) {
        close(this->sock);
    }

    this->request_str = buf;
}
