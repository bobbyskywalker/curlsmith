#pragma once

#define CURLSMITH_VERSION "0.1"

#include <vector>
#include <string>
#include <sstream>

bool                        isBodyInMethod(HttpMethod method);
std::vector<std::string>    splitLines(const std::string& str);