#include "../inc/CommandBuilder.hpp"

std::string CommandBuilder::buildCurlCmd(HttpMethod method, const std::string& url, const std::string& body,
                const std::vector<std::shared_ptr<HeaderData> >&  headersData) {

    const std::string baseToken = "curl";
    const std::string methodToken = "-X";
    const std::string headerToken = "-H";
    const std::string bodyToken = "-d";

    std::string result = baseToken;
    result += " " + methodToken + " " + std::to_string(static_cast<int>(method)) + " " + url;
    for (const auto& header : headersData) {
        result += " " + headerToken + " " + header->key + ": " + header->value;
    }
    result += " " + bodyToken + " \"" + body + "\"";
    return result;
}
