cmake_minimum_required(VERSION 3.27)
project(HTTP
        VERSION 1.0
        DESCRIPTION "HTTP"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_7_1
)
FetchContent_MakeAvailable(curl)

add_executable(HTTP main.cpp
        CURL.h
        CURL.cpp)
target_link_libraries(HTTP libcurl)