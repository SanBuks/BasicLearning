#include <winsock2.h>
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