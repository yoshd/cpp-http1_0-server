#include <iostream>
#include "httpresponseheader.h"
#include "httpresponse.h"
#include "gtest/gtest.h"

TEST(HTTPResponseHeaderTest, TestContentLength) {
    HTTPResponseHeader *h = new HTTPResponseHeader();
    h->set_content_length("<h1>Hello, world!</h1>");
    int content_length = h->get_content_length();
    int expect = 22;
    EXPECT_EQ(content_length, expect);
}

TEST(HTTPResponseHeaderTest, TestContentType) {
    HTTPResponseHeader *h = new HTTPResponseHeader();
    h->set_content_type(ContentType::TextPlain);
    std::string content_type_str = h->get_content_type_str();
    std::string expect = "text/plain";
    EXPECT_EQ(content_type_str, expect);
}

TEST(HTTPResponseHeaderTest, TestResponseHeaderString) {
    HTTPResponseHeader *h = new HTTPResponseHeader();
    h->set_content_length("<h1>Hello, world!</h1>");
    std::string header_str = h->get_header_str();
    std::string expect = "Content-Type: text/html\r\nServer: my-cpp\r\nContent-Length: 22\r\n";
    EXPECT_EQ(header_str, expect);
}

TEST(HTTPResponseTest, TestGetStatusCodeString) {
    HTTPResponse *hr = new HTTPResponse();
    hr->set_status_code(200);
    std::string status_code_str = hr->get_status_code_str();
    std::string expect = "200 OK";
    EXPECT_EQ(status_code_str, expect);
}

TEST(HTTPResponseTest, TestResponseHeader) {
    HTTPResponse *hr = new HTTPResponse();
    hr->set_body("<h1>hello</h1>");
    std::string response = hr->get_response_str();
    std::string res = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nServer: my-cpp\r\nContent-Length: 14\r\n\r\n<h1>hello</h1>";
    EXPECT_EQ(response, res);
}

