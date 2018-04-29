#ifndef INCLUDED_HTTPHandler_h_
#define INCLUDED_HTTPHandler_h_
#include <string>
#include "httpresponse.h"

class HTTPHandler {
    public:
        static HTTPResponse* make_response(std::string request_str);
};

#endif
