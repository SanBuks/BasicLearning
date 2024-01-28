#if defined(__clang__)
#include "arpa/inet.h"
#elif defined(__GNUC__) || defined(__GNUG__)
#include "arpa/inet.h"
#elif defined(_MSC_VER)
#include <winsock2.h>
#endif

#include <iostream>
#include <format>

int main() {
  std::cout << std::format("machine size is {}\n", sizeof(char *));
  std::cout << std::format("long size is {}\n", sizeof(long));

  unsigned long n = 1;
  auto nn = htonl(n);
  std::cout << std::format("host: {}({:#x}) -> net: {}({:#x})\n",n, n, nn, nn);
  return 0;
}