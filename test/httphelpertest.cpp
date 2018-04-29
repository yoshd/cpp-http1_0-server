#include <string>
#include "httphelper.h"
#include "notfoundexception.h"
#include "httpresponseheader.h"
#include "gtest/gtest.h"

TEST(HTTPHelperTest, TestGetContent) {
    std::string html_index1 = HTTPHelper::get_content("/index.html");
    std::string html_index2 = HTTPHelper::get_content("/");
    std::string expect_index = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<link rel=\"stylesheet\" type=\"text/css\" href=\"styles/style.css\">\n<title>HelloWorld</title>\n</head>\n<body>\n<h1>Hello, world!</h1>\n<p>こんにちは、世界!</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_index1, expect_index);
    EXPECT_EQ(html_index2, expect_index);
    std::string html_test = HTTPHelper::get_content("/test.html");
    std::string expect_test = "<!DOCTYPE html >\n<html lang=\"ja\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\n<title>Test</title>\n</head>\n<body>\n<h1>Test</h1>\n<p>テスト用</p>\n</body>\n</html>\n";
    EXPECT_EQ(html_test, expect_test);
}

TEST(HTTPHelperTest, TestGetContentNotFound) {

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

TEST(HTTPHelperTest, TestDetermineContentType) {
    ContentType html1 = HTTPHelper::determine_content_type("/index.html");
    ContentType html2 = HTTPHelper::determine_content_type("/index.htm");
    ContentType css = HTTPHelper::determine_content_type("/style.css");
    ContentType jpeg1 = HTTPHelper::determine_content_type("/test.jpeg");
    ContentType jpeg2 = HTTPHelper::determine_content_type("/test.jpg");
    ContentType png1 = HTTPHelper::determine_content_type("/test.png");
    ContentType png2 = HTTPHelper::determine_content_type("/test.PNG");
    ContentType png3 = HTTPHelper::determine_content_type("/favicon.ico");
    ContentType gif = HTTPHelper::determine_content_type("/test.gif");
    ContentType text = HTTPHelper::determine_content_type("/test.txt");

    ContentType expect_html = ContentType::TextHTML;
    ContentType expect_css = ContentType::TextCSS;
    ContentType expect_jpeg = ContentType::ImageJPEG;
    ContentType expect_png = ContentType::ImagePNG;
    ContentType expect_gif = ContentType::ImageGIF;
    ContentType expect_text = ContentType::TextPlain;

    EXPECT_EQ(html1, expect_html);
    EXPECT_EQ(html2, expect_html);
    EXPECT_EQ(css, expect_css);
    EXPECT_EQ(jpeg1, expect_jpeg);
    EXPECT_EQ(jpeg2, expect_jpeg);
    EXPECT_EQ(png1, expect_png);
    EXPECT_EQ(png2, expect_png);
    EXPECT_EQ(png3, expect_png);
    EXPECT_EQ(gif, expect_gif);
    EXPECT_EQ(text, expect_text);
}

TEST(HTTPHelperTest, TestGetContentCGI) {
    std::string test_cgi1 = HTTPHelper::get_content("/test.cgi");
    std::string test_cgi2 = HTTPHelper::get_content("/test.py");
    std::string expect_cgi = "OK Test CGI\n";

    EXPECT_EQ(test_cgi1, expect_cgi);
    EXPECT_EQ(test_cgi2, expect_cgi);
}
