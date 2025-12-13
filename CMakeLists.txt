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
# Automatically find all source files
# ------------------------------------------------------------
file(GLOB_RECURSE CURLSMITH_SOURCES
				src/*.cpp
)

add_executable(curlsmith_app
				${CURLSMITH_SOURCES}
)

target_link_libraries(curlsmith_app
				PRIVATE
								ftxui::screen
								ftxui::dom
								ftxui::component
)

install(TARGETS curlsmith_app)
