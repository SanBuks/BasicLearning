cmake_minimum_required(VERSION 3.27)
project(network)

set(CMAKE_CXX_STANDARD 23)

add_executable(01_byte_order src/01_byte_order.cc)
target_link_libraries(01_byte_order ws2_32)

add_subdirectory(lab)
