#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <format>
#include <iostream>

#include "socket_util.h"
#include "csapp.h"

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << std::format("usage: {} <port>", argv[0]);
    exit(1);
  }

  char *port = argv[2];
  auto listen_fd = util::OpenServerFd(port);
  if (listen_fd < 0) {
    exit(1);
  }

  while (true) {

  }

  exit(0);
}