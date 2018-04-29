#include <string>
#include "httpresponseheader.h"
#include "httpresponse.h"
#include "httprequestparser.h"
#include "httphelper.h"
#include "httprequest.h"
#include "httphandler.h"
#include "notfoundexception.h"
#include "notimplementedexception.h"
#include "badrequestexception.h"

HTTPResponse* HTTPHandler::make_response(std::string request_str) {

    HTTPRequest* req;
    try {
        req = HTTPRequestParser::parse(request_str);
    } catch(NotImplementedException nie) {
        std::string body = HTTPHelper::get_content("/not_implemented.html");
        HTTPResponseHeader *hh = new HTTPResponseHeader(ContentType::TextHTML, "my-cpp");
        HTTPResponse *response = new HTTPResponse(hh);
        response->set_body(body);
        response->set_status_code(nie.get_err_code());
        return response;
    } catch(BadRequestException bre) {
        std::string body = HTTPHelper::get_content("/bad_request.html");
        HTTPResponseHeader *hh = new HTTPResponseHeader(ContentType::TextHTML, "my-cpp");
        HTTPResponse *response = new HTTPResponse(hh);
        response->set_body(body);
        response->set_status_code(bre.get_err_code());
        return response;
    }

    ContentType content_type = HTTPHelper::determine_content_type(req->get_path());

    HTTPResponseHeader *hh = new HTTPResponseHeader(content_type, "my-cpp");
    HTTPResponse *response = new HTTPResponse(hh);

    std::string body;
    try {
        body = HTTPHelper::get_content(req->get_path());
        response->set_status_code(200);
    } catch(NotFoundException nfe) {
        body = HTTPHelper::get_content("/not_found.html");
        response->set_status_code(nfe.get_err_code());
        response->set_header_content_type(ContentType::TextHTML);
    }

    response->set_body(body);

    if (req->get_method() == "HEAD") {
        response->set_head_flag(true);
    }
    return response;
}
