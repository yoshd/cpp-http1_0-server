#include <string>
#include "httphelper.h"
#include "gtest/gtest.h"

TEST(HTTPHelperTest, TestGetHtml) {
    std::string html_index1 = HTTPHelper::get_html("/index.html");
    std::string html_index2 = HTTPHelper::get_html("/");
    std::string html_index3 = HTTPHelper::get_html("/favicon.ico");
    std::string expect_index = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>HelloWorld</title>\n</head>\n<body>\n<h1>Hello, world!</h1>\n<p>こんにちは、世界!</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_index1, expect_index);
    EXPECT_EQ(html_index2, expect_index);
    EXPECT_EQ(html_index3, expect_index);
    std::string html_test = HTTPHelper::get_html("/test.html");
    std::string expect_test = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>Test</title>\n</head>\n<body>\n<h1>Test</h1>\n<p>テスト用</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_test, expect_test);
}
