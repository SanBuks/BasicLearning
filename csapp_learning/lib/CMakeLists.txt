project(lib)

add_library(csapp STATIC
  csapp/csapp.h
  csapp/csapp.c
)
target_include_directories(csapp PUBLIC csapp)
target_link_libraries(csapp PUBLIC pthread)

add_library(util STATIC
  util/socket_util.h
  util/socket_util.cc
  util/io_util.h
  util/io_util.cc
)
target_include_directories(util PUBLIC util)
