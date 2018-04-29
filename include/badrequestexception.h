#ifndef INCLUDED_BadRequestException_h_
#define INCLUDED_BadRequestException_h_
#include <string>
#include "httpexception.h"

class BadRequestException : public HTTPException {
    private:
        int err_code;
        std::string err_msg;
    public:
        BadRequestException() {
            this->err_code = 400;
            this->err_msg = "Bad Request";
        }
        int get_err_code() { return this->err_code; }
        std::string get_err_msg() { return this->err_msg; }
};

#endif
