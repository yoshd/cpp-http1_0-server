#ifndef INCLUDED_NotImplementedException_h_
#define INCLUDED_NotImplementedException_h_
#include <string>
#include "httpexception.h"

class NotImplementedException : public HTTPException {
    private:
        int err_code;
        std::string err_msg;
    public:
        NotImplementedException() {
            this->err_code = 501;
            this->err_msg = "Not Implemented";
        }
        int get_err_code() { return this->err_code; }
        std::string get_err_msg() { return this->err_msg; }
};

#endif
