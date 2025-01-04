#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <format>
#include <iostream>

#include "socket_util.h"
#include "csapp.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    std::cout << std::format("usage: {} <host> <port>", argv[0]);
    exit(1);
  }

  char *host = argv[1];
  char *port = argv[2];
  auto client_fd = util::OpenClientFd(host, port);
  if (client_fd < 0) {
    exit(1);
  }

  rio_t rio;
  char buf[1024]{};
  Rio_readinitb(&rio, client_fd);
  while (Fgets(buf, 1024, stdin) != nullptr) {
    Rio_writen(client_fd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, 1024);
    Fputs(buf, stdout);
  }
  close(client_fd);
  exit(0);
}