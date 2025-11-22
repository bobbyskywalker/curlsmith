#include "../inc/CommandBuilder.hpp"

std::string CommandBuilder::buildCurlCmd(const HttpMethod method, const std::string& url, const std::string& body,
                const std::vector<std::shared_ptr<HeaderData>>&  headersData) {

    const std::string baseToken = "curl";
    const std::string methodToken = "-X";
    const std::string headerToken = "-H";
    const std::string bodyToken = "-d";

    std::string result = baseToken + " " + methodToken + " " + httpMethodToString(method) + " " + url;

    if (!headersData.empty()) {
        for (const auto& header : headersData) {
            result += " \\\n" + headerToken + " \"" + header->key + ": " + header->value + "\"";
        }
    }

    if (!body.empty()) {
        result += " \\\n" + bodyToken + " '" + body + "'";
    }

    return result;
}
