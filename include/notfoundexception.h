#ifndef INCLUDED_NotFoundException_h_
#define INCLUDED_NotFoundException_h_
#include <string>
#include "httpexception.h"

class NotFoundException : public HTTPException {
    private:
        int err_code;
        std::string err_msg;
    public:
        NotFoundException() {
            this->err_code = 404;
            this->err_msg = "Not Found";
        }
        int get_err_code() { return this->err_code; }
        std::string get_err_msg() { return this->err_msg; }
};

#endif
