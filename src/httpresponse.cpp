#include <string>
#include <unordered_map>
#include "httpresponseheader.h"
#include "httpresponse.h"

const std::unordered_map<int, std::string> HTTPResponseCode::code_map = {
    {200, "OK"},
    {400, "Bad Request"}
};

HTTPResponse::HTTPResponse() {
    this->status_code = 200;
    this->message = HTTPResponseCode::code_map.at(200);
    this->header = new HTTPResponseHeader();
    this->body = "";
}

HTTPResponse::HTTPResponse(int status_code, HTTPResponseHeader *header, std::string body) {
    this->status_code = status_code;
    this->message = HTTPResponseCode::code_map.at(status_code);
    this->header = header;
    this->body = body;

    this->header->set_content_length(body);
}

void HTTPResponse::set_status_code(int code) {
    this->status_code = code;
    this->message = HTTPResponseCode::code_map.at(code);
}

std::string HTTPResponse::get_status_code_str(void) {
    std::string status_code_str = std::to_string(this->status_code) + " " + this->message;
    return status_code_str;
}

void HTTPResponse::set_body(std::string body) {
    this->body = body;
    this->header->set_content_length(body);
}

std::string HTTPResponse::get_response_str(void) {
    std::string response_str = "HTTP/1.0 "
            + this->get_status_code_str() + "\r\n"
            + this->header->get_header_str()
            + "\r\n"
            + this->body;
    return response_str;
}

HTTPResponse::~HTTPResponse() {
    delete header;
}
