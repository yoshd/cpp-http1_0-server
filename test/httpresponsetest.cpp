#include <string>
#include "httpresponseheader.h"
#include "httpresponse.h"
#include "gtest/gtest.h"

TEST(HTTPResponseTest, TestGetStatusCodeString) {
    HTTPResponse *hr = new HTTPResponse();
    hr->set_status_code(200);
    std::string status_code_200 = hr->get_status_code_str();
    std::string expect_200 = "200 OK";
    EXPECT_EQ(status_code_200, expect_200);
    hr->set_status_code(400);
    std::string status_code_400 = hr->get_status_code_str();
    std::string expect_400 = "400 Bad Request";
    EXPECT_EQ(status_code_400, expect_400);
}

TEST(HTTPResponseTest, TestResponse) {
    HTTPResponse *hr = new HTTPResponse();
    hr->set_body("<h1>hello</h1>");
    std::string response = hr->get_response_str();
    std::string res = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nServer: my-cpp\r\nContent-Length: 14\r\n\r\n<h1>hello</h1>";
    EXPECT_EQ(response, res);
}
