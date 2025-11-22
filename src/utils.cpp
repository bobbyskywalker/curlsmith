#include "../inc/HttpMethod.hpp"
#include "../inc/curlsmith.hpp"

bool isBodyInMethod(const HttpMethod method) {
    if (method == HttpMethod::POST || method == HttpMethod::PUT || method == HttpMethod::PATCH)
        return true;
    return false;
}

std::vector<std::string> splitLines(const std::string &str) {
    std::vector<std::string> lines;
    std::stringstream ss(str);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string httpMethodToString(const HttpMethod method) {
    switch (method) {
        case HttpMethod::GET: return "GET";
        case HttpMethod::POST: return "POST";
        case HttpMethod::PUT: return "PUT";
        case HttpMethod::DELETE: return "DELETE";
        case HttpMethod::PATCH: return "PATCH";
        case HttpMethod::HEAD: return "HEAD";
        case HttpMethod::OPTIONS: return "OPTIONS";
    }
    return "GET";
}
