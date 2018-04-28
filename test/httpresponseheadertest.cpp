#include <string>
#include "httpresponseheader.h"
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
