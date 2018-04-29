#include <string>
#include <unordered_map>
#include "httprequest.h"

HTTPRequest::HTTPRequest(std::string method, std::string path, std::unordered_map<std::string, std::string> queries, std::string version, std::unordered_map<std::string, std::string> headers, std::string body) {
    this->method = method;
    this->path = path;
    this->queries = queries;
    this->version = version;
    this->headers = headers;
    this->body = body;
}
