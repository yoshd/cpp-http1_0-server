#ifndef INCLUDED_HTTPResponseHeader_h_
#define INCLUDED_HTTPResponseHeader_h_
#include <string>

enum class ContentType {
    TextHTML,
    TextPlain,
};

class HTTPResponseHeader {
    private:
        ContentType content_type;
        std::string server;
        int content_length;
    public:
        HTTPResponseHeader();
        HTTPResponseHeader(ContentType content_type, std::string server);
        void set_content_type(ContentType ct) { this->content_type = ct; }
        ContentType get_content_type(void) { return this->content_type; }
        std::string get_content_type_str(void);
        void set_server(std::string server) { this->server = server; }
        std::string get_server(void) { return this->server; }
        void set_content_length(std::string content);
        int get_content_length(void) { return this->content_length; }
        std::string get_header_str(void);
};

#endif
