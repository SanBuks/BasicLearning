cmake_minimum_required(VERSION 3.15)
project(csapp LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD          20    CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON    CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE            Debug CACHE INTERNAL "")

add_subdirectory(lib)

add_subdirectory(ch01)
add_subdirectory(ch02)

add_subdirectory(ch11_network)
