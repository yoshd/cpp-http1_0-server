#ifndef INCLUDED_HTTPHelper_h_
#define INCLUDED_HTTPHelper_h_
#include <string>
#include "notfoundexception.h"

class HTTPHelper {
    public:
        static std::string get_content(std::string path) throw(NotFoundException);
};

#endif
