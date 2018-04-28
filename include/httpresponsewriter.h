#ifndef INCLUDED_HTTPResponseWriter_h_
#define INCLUDED_HTTPResponseWriter_h_
#include "httpresponse.h"

class HTTPResponseWriter {
    private:
        int sock;
    public:
        HTTPResponseWriter(int sock);
        void write_response(HTTPResponse *response);
};

#endif
