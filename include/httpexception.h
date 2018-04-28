#ifndef INCLUDED_HTTPException_h_
#define INCLUDED_HTTPException_h_
#include <string>

class HTTPException {
    public:
        virtual int get_err_code() = 0;
        virtual std::string get_err_msg() = 0;
};

#endif
