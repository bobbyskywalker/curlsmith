cmake_minimum_required(VERSION 3.15)

project(
    curlsmith
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ------------------------------------------------------------
# FTXUI
# ------------------------------------------------------------
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# ------------------------------------------------------------
# spdlog
# ------------------------------------------------------------
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

# ------------------------------------------------------------
# curlsmith executable
# ------------------------------------------------------------
add_executable(curlsmith_app
    src/main.cpp
)

target_link_libraries(curlsmith_app
    PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component
        spdlog::spdlog_header_only
)

install(TARGETS curlsmith_app)
