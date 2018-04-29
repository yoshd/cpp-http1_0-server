#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>
#include "httphelper.h"
#include "notfoundexception.h"

std::string HTTPHelper::get_content(std::string path) throw(NotFoundException) {

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

    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    std::string content(it, last);

    return content;
}
