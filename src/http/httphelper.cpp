#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "httphelper.h"
#include "notfoundexception.h"
#include "httpresponseheader.h"

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

std::string execute_cgi(std::string path) throw(NotFoundException) {
    std::string cgi_suf = ".cgi";
    std::string py_suf = ".py";
    int pos = path.rfind(cgi_suf);
    int len = cgi_suf.length();
    if (pos != std::string::npos) {
        path.replace(pos, len, py_suf);
    }

    std::string cgi_path = "../cgi" + path;
    std::ifstream ifs(cgi_path);
    if (ifs.fail()) {
        throw NotFoundException();
    }
    std::string cmd = "python3 " + cgi_path;
    char *cmd_ch = new char[cmd.size() + 1];
    cmd_ch = const_cast<char*>(cmd.c_str());
    FILE* fp;
    char buf[2048];
    fp = popen(cmd_ch, "r");
    std::string result;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        result += buf;
    }
    pclose(fp);
    std::cout<<result;
    return result;
}

std::string HTTPHelper::get_content(std::string path) throw(NotFoundException) {

    std::string fname;
    if (path == "/") {
        fname = "../static/index.html";
    } else if (ends_with(path, ".cgi") || ends_with(path, ".py")) {
        return execute_cgi(path);
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

    if (ends_with(path_lower, html_suf) || ends_with(path_lower, htm_suf) || path == "/" || ends_with(path_lower, ".cgi") || ends_with(path_lower, ".py")) {
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
