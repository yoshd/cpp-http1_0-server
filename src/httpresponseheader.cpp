#include <string>
#include "httpresponseheader.h"

HTTPResponseHeader::HTTPResponseHeader() {
    this->content_type = ContentType::TextHTML;
    this->server = "my-cpp";
    this->content_length = 0;
}
HTTPResponseHeader::HTTPResponseHeader(ContentType content_type, std::string server) {
    this->content_type = content_type;
    this->server = server;
    this->content_length = 0;
}

void HTTPResponseHeader::set_content_length(std::string content) {
    this->content_length = content.size();
}

std::string HTTPResponseHeader::get_content_type_str(void) {
    std::string content_type_str;
    switch (this->content_type) {
        case ContentType::TextHTML:
            content_type_str = "text/html";
            break;
        case ContentType::TextPlain:
            content_type_str = "text/plain";
            break;
    }
    return content_type_str;
}

std::string HTTPResponseHeader::get_header_str(void) {
    std::string header = "Content-Type: " + this->get_content_type_str() + "\r\n"
            + "Server: " + this->server + "\r\n"
            + "Content-Length: " + std::to_string(this->content_length) + "\r\n";
    return header;
}
