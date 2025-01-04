#include <arpa/inet.h>

#include <iostream>
#include <format>

//  Internet address
//  struct in_addr {
//    uint32_t s_addr;
//  };

int main() {
  const char *address = "205.188.160.121";
  in_addr addr{};
  if (inet_pton(AF_INET, address, &addr) < 0) {
    std::cout << std::format("error: {}\n", errno);
    return 1;
  }
  std::cout << std::format("address {} in network byte order: 0x{:X}\n", address, addr.s_addr);
  std::cout << std::format("address {} in little edian byte order: 0x{:X}\n", address, ntohl(addr.s_addr));


  const char *result;
  addr.s_addr = htonl(0xC0A80001); // 192.168.0.1
  char ip_buf[INET_ADDRSTRLEN];
  result = inet_ntop(AF_INET, &addr, ip_buf, INET_ADDRSTRLEN);
  if (!result) {
    std::cout << std::format("error: conversion failed!\n");
  }
  std::cout << std::format("address network byte order {:X} presentation: {}", addr.s_addr, ip_buf);
  return 0;
}
