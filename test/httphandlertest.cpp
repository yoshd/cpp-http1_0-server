#include <string>
#include "httphandler.h"
#include "httpresponse.h"
#include "gtest/gtest.h"

TEST(HTTPHandlerTest, TestMakeResponse) {
    std::string req_str = "GET /index.html HTTP/1.1\r\nHost: localhost:8888\r\nUser-Agent: curl/7.52.1\r\nAccept: */*";
    HTTPResponse *response = HTTPHandler::make_response(req_str);

    int expect_status_code = 200;
    std::string expect_status_code_str = "200 OK";
    std::string expect_response_str = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nServer: my-cpp\r\nContent-Length: 285\r\n\r\n<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<link rel=\"stylesheet\" type=\"text/css\" href=\"styles/style.css\">\n<title>HelloWorld</title>\n</head>\n<body>\n<h1>Hello, world!</h1>\n<p>こんにちは、世界!</p>\n</body>\n</html>\n";

    EXPECT_EQ(response->get_status_code(), expect_status_code);
    EXPECT_EQ(response->get_status_code_str(), expect_status_code_str);
    EXPECT_EQ(response->get_response_str(), expect_response_str);
}

TEST(HTTPHandlerTest, TestMakeResponseImageHead) {
    std::string req_str = "HEAD /images/hiyoko_baby.png HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.52.1\r\nAccept: */*";
    HTTPResponse *response = HTTPHandler::make_response(req_str);

    int expect_status_code = 200;
    std::string expect_status_code_str = "200 OK";
    std::string expect_response_str = "HTTP/1.0 200 OK\r\nContent-Type: image/png\r\nServer: my-cpp\r\nContent-Length: 130982\r\n";

    EXPECT_EQ(response->get_status_code(), expect_status_code);
    EXPECT_EQ(response->get_status_code_str(), expect_status_code_str);
    EXPECT_EQ(response->get_response_str(), expect_response_str);
}

TEST(HTTPHandlerTest, TestMakeResponseNotFound) {
    std::string req_str = "GET /hoge HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.52.1\r\nAccept: */*";
    HTTPResponse *response = HTTPHandler::make_response(req_str);

    int expect_status_code = 404;
    std::string expect_status_code_str = "404 Not Found";
    std::string expect_response_str = "HTTP/1.0 404 Not Found\r\nContent-Type: text/html\r\nServer: my-cpp\r\nContent-Length: 244\r\n\r\n<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>404: Not Found</title>\n</head>\n<body>\n<h1>お探しのページは見つかりません。(404: Not Found) </h1>\n</body>\n</html>\n";

    EXPECT_EQ(response->get_status_code(), expect_status_code);
    EXPECT_EQ(response->get_status_code_str(), expect_status_code_str);
    EXPECT_EQ(response->get_response_str(), expect_response_str);
}
