#include <fstream>
#include <iostream>
#include <string>
#include "httphelper.h"
#include "notfoundexception.h"

std::string HTTPHelper::get_html(std::string path) throw(NotFoundException) {

    std::string fname;
    if (path == "/" || path == "index.html" || path == "/favicon.ico") {
        fname = "../static/index.html";
    } else {
        fname = "../static" + path;
    }

    std::ifstream ifs(fname);

    if (ifs.fail()) {
        throw NotFoundException();
    }

    std::string html;
    std::string str;
    while (getline(ifs, str)) {
        html += str + "\n";
    }

    return html;
}
