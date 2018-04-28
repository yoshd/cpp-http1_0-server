#ifndef INCLUDED_HTTPResponse_h_
#define INCLUDED_HTTPResponse_h_
#include <string>
#include <unordered_map>
#include "httpresponseheader.h"

class HTTPResponseCode {
    public:
        static const std::unordered_map<int, std::string> code_map;
};

class HTTPResponse {
    private:
        int status_code;
        std::string message;
        HTTPResponseHeader *header;
        std::string body;
    public:
        HTTPResponse();
        HTTPResponse(int status_code, HTTPResponseHeader *header, std::string body);
        void set_status_code(int code);
        int get_status_code(void) { return this->status_code; }
        std::string get_status_code_str(void);
        void set_header(HTTPResponseHeader *header) { this->header = header; }
        HTTPResponseHeader* get_header(void) { return this->header; }
        void set_body(std::string body);
        std::string get_body(void) { return this->body; }
        std::string get_response_str(void);
        ~HTTPResponse();
};

#endif
