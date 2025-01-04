#include "io_util.h"

#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <format>
#include <iostream>

namespace util {

void Close(int fd) {
  if (close(fd) < 0) {
    std::cerr << std::format("close file description failed: {}\n", strerror(errno));
    std::cerr << std::format("exited\n");
    exit(EXIT_FAILURE);
  }
}



}