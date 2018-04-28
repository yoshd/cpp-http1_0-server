#ifndef INCLUDED_HTTPRequest_h_
#define INCLUDED_HTTPRequest_h_
#include <string>
#include <unordered_map>

class HTTPRequest {
    private:
        std::string method;
        std::string path;
        std::unordered_map<std::string, std::string> queries;
        std::string version;
        std::unordered_map<std::string, std::string> headers;
        std::string body;
    public:
        HTTPRequest(std::string method, std::string path, std::unordered_map<std::string, std::string> queries, std::string version, std::unordered_map<std::string, std::string> headers, std::string body);
        std::string get_method(void) { return this->method; }
        std::string get_path(void) { return this->path; }
        std::unordered_map<std::string, std::string> get_queries(void) { return this->queries; }
        std::string get_version(void) { return this->version; }
        std::unordered_map<std::string, std::string> get_headers(void) { return this->headers; }
        std::string get_body(void) { return this->body; }
};

#endif
