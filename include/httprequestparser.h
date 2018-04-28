#ifndef INCLUDED_HTTPRequestParser_h_
#define INCLUDED_HTTPRequestParser_h_
#include <string>
#include "httprequest.h"

class HTTPRequestParser {
    public:
        static HTTPRequest* parse(std::string request_str);
};

#endif
