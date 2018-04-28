#include <string>
#include <unordered_map>
#include <regex>
#include <vector>
#include <sstream>
#include "httprequest.h"
#include "httprequestparser.h"
#include "notimplementedexception.h"

std::vector<std::string> split_in_two(std::string str, std::string separator) {

    std::string::size_type separator_length = separator.length();
    std::vector<std::string> list = std::vector<std::string>();

    if (separator_length == 0) {
        list.push_back(str);
    } else {
        std::string::size_type pos = str.find(separator);
        if (pos == std::string::npos) {
            list.push_back(str);
        }
        list.push_back(str.substr(0, pos));
         list.push_back(str.substr(pos + separator_length));
    }

    return list;
}

std::vector<std::string> split(std::string str, std::string separator) {

    std::string::size_type separator_length = separator.length();
    std::vector<std::string> list = std::vector<std::string>();

    if (separator_length == 0) {
        list.push_back(str);
    } else {
        std::string::size_type offset = std::string::size_type(0);
        while (1) {
            std::string::size_type pos = str.find(separator, offset);
            if (pos == std::string::npos) {
                list.push_back(str.substr(offset));
                break;
            }
            list.push_back(str.substr(offset, pos - offset));
            offset = pos + separator_length;
        }
    }

    return list;
}

// Parse the string of the form "key1=val1&key2=val2"
std::unordered_map<std::string, std::string> parse_kv(std::string key_value_pairs) {
    std::unordered_map<std::string, std::string> kv_pairs;
    std::vector<std::string> kv_pairs_vec = split(key_value_pairs, "&");
    for (std::string kv_pair_str : kv_pairs_vec) {
        std::vector<std::string> kv_pair_vec = split_in_two(kv_pair_str, "=");
        if (kv_pair_vec.size() == 2) {
            std::string key = kv_pair_vec[0];
            std::string value = kv_pair_vec[1];
            kv_pairs[key] = value;
        }
    }
    return kv_pairs;
}

bool is_implemented_method(std::string method) {
    return method == "GET" || method == "HEAD" || method == "POST";
}

HTTPRequest* HTTPRequestParser::parse(std::string request_str) throw(NotImplementedException) {
    std::regex first_line_re(R"(^([A-Z]{3,})\s(/[^?\s]*)\??(.*)\s(HTTP/[0-9]\.[0-9]))");
    std::regex header_kv_re(R"((.+?)\s?:\s?(.+))");
    std::string separater = "\r\n\r\n";

    std::vector<std::string> request_vec = split_in_two(request_str, separater);
    std::vector<std::string> header_lines;
    if (request_vec.size() != 0) {
        header_lines = split(request_vec[0], "\r\n");
    }

    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> queries;
    std::unordered_map<std::string, std::string> headers;

    if (header_lines.size() >= 2) {
        std::smatch first_line_matched;
        if (std::regex_match(header_lines[0], first_line_matched, first_line_re)) {

            method = first_line_matched[1].str();
            if (!is_implemented_method(method)) {
                throw NotImplementedException();
            }

            path = first_line_matched[2].str();
            queries = parse_kv(first_line_matched[3].str());
            version = first_line_matched[4].str();
        }
        header_lines.erase(header_lines.begin());
        std::smatch header_kv_matched;
        for (std::string line : header_lines) {
            if (std::regex_match(line, header_kv_matched, header_kv_re)) {
                std::string key = header_kv_matched[1].str();
                std::string value = header_kv_matched[2].str();
                headers[key] = value;
            }
        }
    }

    std::string body;
    if (request_vec.size() == 2) {
        body = request_vec[1];
    }
    HTTPRequest *hr = new HTTPRequest(method, path, queries, version, headers, body);
    return hr;
}
