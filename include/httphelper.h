#ifndef INCLUDED_HTTPHelper_h_
#define INCLUDED_HTTPHelper_h_
#include <string>
#include "notfoundexception.h"
#include "httpresponseheader.h"

class HTTPHelper {
    public:
        static std::string get_content(std::string path) throw(NotFoundException);
        static ContentType determine_content_type(std::string path);
};

#endif
