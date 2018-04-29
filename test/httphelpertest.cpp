#include <string>
#include "httphelper.h"
#include "notfoundexception.h"
#include "gtest/gtest.h"

TEST(HTTPHelperTest, TestGetHtml) {
    std::string html_index1 = HTTPHelper::get_content("/index.html");
    std::string html_index2 = HTTPHelper::get_content("/");
    std::string html_index3 = HTTPHelper::get_content("/favicon.ico");
    std::string expect_index = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<link rel=\"stylesheet\" type=\"text/css\" href=\"styles/style.css\">\n<title>HelloWorld</title>\n</head>\n<body>\n<h1>Hello, world!</h1>\n<p>こんにちは、世界!</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_index1, expect_index);
    EXPECT_EQ(html_index2, expect_index);
    EXPECT_EQ(html_index3, expect_index);
    std::string html_test = HTTPHelper::get_content("/test.html");
    std::string expect_test = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>Test</title>\n</head>\n<body>\n<h1>Test</h1>\n<p>テスト用</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_test, expect_test);
}

TEST(HTTPHelperTest, TestGetHtmlNotFound) {

    std::string html;
    try {
        html = HTTPHelper::get_content("/hoge");
    } catch(NotFoundException nfe) {
        html = HTTPHelper::get_content("/not_found.html");
    }

    std::string expect_html = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>404: Not Found</title>\n</head>\n<body>\n<h1>お探しのページは見つかりません。(404: Not Found) </h1>\n</body>\n</html>\n";

    EXPECT_EQ(html, expect_html);
    ASSERT_THROW(HTTPHelper::get_content("/hoge"), NotFoundException);
}
