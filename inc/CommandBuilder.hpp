#pragma once

#include <string>

#include "AppInterface.hpp"
#include "HttpMethod.hpp"

class CommandBuilder {
public:
        static std::string buildCurlCmd(HttpMethod method, const std::string& url, const std::string& body,
                const std::vector<std::shared_ptr<HeaderData> > & headersData);

};
