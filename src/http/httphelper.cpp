#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>
#include "httphelper.h"
#include "notfoundexception.h"
#include "httpresponseheader.h"

std::string HTTPHelper::get_content(std::string path) throw(NotFoundException) {

    std::string fname;
    if (path == "/") {
        fname = "../static/index.html";
    } else {
        fname = "../static" + path;
    }

    std::ifstream ifs(fname);

    if (ifs.fail()) {
        throw NotFoundException();
    }

    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string content(it, last);

    return content;
}

bool starts_with(std::string str, std::string start_str) {
    return str.size() >= str.size() && std::equal(std::begin(start_str), std::end(start_str), std::begin(str));
}

bool ends_with(std::string str, std::string start_str) {
    return str.size() >= start_str.size() && str.find(start_str, str.size() - start_str.size()) != std::string::npos;
}

std::string lower(std::string str) {
    std::string lo;
    lo.resize(str.size());
    std::transform(str.cbegin(), str.cend(), lo.begin(), ::tolower);
    return lo;
}

ContentType HTTPHelper::determine_content_type(std::string path) {

    std::string html_suf = ".html";
    std::string htm_suf = ".htm";
    std::string img_suf_jpg = ".jpg";
    std::string img_suf_jpeg = ".jpeg";
    std::string img_suf_png = ".png";
    std::string img_suf_gif = ".gif";
    std::string css_suf = ".css";

    std::string path_lower = lower(path);
    ContentType content_type;

    if (ends_with(path_lower, html_suf) || ends_with(path_lower, htm_suf) || path == "/") {
        content_type = ContentType::TextHTML;
    } else if (ends_with(path_lower, img_suf_jpg) || ends_with(path_lower, img_suf_jpeg)) {
        content_type = ContentType::ImageJPEG;
    } else if (ends_with(path_lower, img_suf_png) || path == "/favicon.ico") {
        content_type = ContentType::ImagePNG;
    } else if (ends_with(path_lower, img_suf_gif)) {
        content_type = ContentType::ImageGIF;
    } else if (ends_with(path_lower, css_suf)) {
        content_type = ContentType::TextCSS;
    } else {
        content_type = ContentType::TextPlain;
    }

    return content_type;
}
