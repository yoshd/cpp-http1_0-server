#include "httprequestreader.h"
#include "httpresponsewriter.h"
#include "httpresponse.h"
#include "httphandler.h"
#include "httpprocessor.h"

int HTTPProcessor::run(int sock) {

    HTTPRequestReader *hrr = new HTTPRequestReader(sock);
    hrr->read_request();

    HTTPResponse *response = HTTPHandler::make_response(hrr->get_request_str());

    HTTPResponseWriter *hrw = new HTTPResponseWriter(sock);
    hrw->write_response(response);

    delete hrr;
    delete response;
    delete hrw;
    return 0;
}
