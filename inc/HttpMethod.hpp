#pragma once

#include <string>

/* mapped to selectedOption in the UI */
enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    HEAD,
    OPTIONS
};

/* string mapper for rendering */
const std::string httpMethodToString(HttpMethod method);
