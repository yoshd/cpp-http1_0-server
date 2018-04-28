#include <string>
#include <unistd.h>
#include <string.h>
#include "httpresponsewriter.h"
#include "httpresponse.h"

HTTPResponseWriter::HTTPResponseWriter(int sock) {
    this->sock = sock;
}

void HTTPResponseWriter::write_response(HTTPResponse *response) {
    std::string res_str = response->get_response_str();
    char* res_char = new char[res_str.size() + 1];
    res_char = const_cast<char*>(res_str.c_str());
    write(this->sock, res_char, strlen(res_char));
    fsync(this->sock);
    close(this->sock);
}
