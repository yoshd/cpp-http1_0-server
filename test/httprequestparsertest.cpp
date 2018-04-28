#include <string>
#include <unordered_map>
#include "httprequestparser.h"
#include "httprequest.h"
#include "gtest/gtest.h"

TEST(HTTPRequestParserTest, TestParseGetRequest) {
    std::string req_get = "GET /index.html?a=b&c=d HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.52.1\r\nAccept: */*";
    HTTPRequest *hr_get = HTTPRequestParser::parse(req_get);

    std::string expect_method_get = "GET";
    std::string expect_path_get = "/index.html";
    std::unordered_map<std::string, std::string> expect_queries_get{
        {"a", "b"},
        {"c", "d"}
    };
    std::string expect_version_get = "HTTP/1.1";
    std::unordered_map<std::string, std::string> expect_headers_get{
        {"Host", "localhost:8080"},
        {"User-Agent", "curl/7.52.1"},
        {"Accept", "*/*"}
    };

    EXPECT_EQ(expect_method_get, hr_get->get_method());
    EXPECT_EQ(expect_path_get, hr_get->get_path());
    EXPECT_EQ(expect_queries_get, hr_get->get_queries());
    EXPECT_EQ(expect_version_get, hr_get->get_version());
    EXPECT_EQ(expect_headers_get, hr_get->get_headers());
}

TEST(HTTPRequestParserTest, TestParsePostRequest) {
    std::string req_post = "POST / HTTP/1.1\r\nHost: example.com\r\nUser-Agent: curl/7.52.1\r\nAccept: */*\r\nContent-Length: 3\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\na=b";
    HTTPRequest *hr_post = HTTPRequestParser::parse(req_post);

    std::string expect_method_post = "POST";
    std::string expect_path_post = "/";
    std::string expect_version_post = "HTTP/1.1";
    std::unordered_map<std::string, std::string> expect_headers_post{
        {"Host", "example.com"},
        {"User-Agent", "curl/7.52.1"},
        {"Accept", "*/*"},
        {"Content-Length", "3"},
        {"Content-Type", "application/x-www-form-urlencoded"}
    };
    std::string expect_body_post = "a=b";

    EXPECT_EQ(expect_method_post, hr_post->get_method());
    EXPECT_EQ(expect_path_post, hr_post->get_path());
    EXPECT_EQ(expect_version_post, hr_post->get_version());
    EXPECT_EQ(expect_headers_post, hr_post->get_headers());
    EXPECT_EQ(expect_body_post, hr_post->get_body());
}
