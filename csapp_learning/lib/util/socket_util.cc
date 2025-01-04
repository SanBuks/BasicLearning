#include "socket_util.h"

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <format>

#include "io_util.h"

namespace util {

bool GetAddrInfo(const char *host, const char *port, const addrinfo *hints, addrinfo **list) {
  if (int rc; (rc = getaddrinfo(host, port, hints, list)) != 0) {
    std::cerr << std::format("getaddrinfo({}:{}) failed: {}\n", host, port, gai_strerror(rc));
    return false;
  }
  return true;
}

bool GetNameInfo(const sockaddr *addr, socklen_t addr_len,
                 char *host_buf, socklen_t host_len,
                 char *port_buf, socklen_t port_len, int flags) {
  if (int rc; (rc = getnameinfo(addr, addr_len, host_buf, host_len, port_buf, port_len, flags)) != 0) {
    std::cerr << std::format("getnameinfo failed: {}\n", gai_strerror(rc));
    return false;
  }
  return true;
}

int Socket(addrinfo *info) {
  int fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
  if (fd < 0) {
    const int kBufSize = 100;
    char host_buf[kBufSize]{};
    if (GetNameInfo(info->ai_addr, info->ai_addrlen, host_buf, kBufSize, nullptr, 0, NI_NUMERICHOST)) {
      std::cerr << std::format("create socket failed({})\n", host_buf);
    } else {
      std::cerr << std::format("create socket failed\n");
    }
  }
  return fd;
}

bool Connect(int fd, addrinfo *info) {
  if (connect(fd, info->ai_addr, info->ai_addrlen) < 0) {
    const int kBufSize = 100;
    char host_buf[kBufSize]{};
    if (GetNameInfo(info->ai_addr, info->ai_addrlen, host_buf, kBufSize, nullptr, 0, NI_NUMERICHOST)) {
      std::cerr << std::format("connect socket failed({})\n", host_buf);
    } else {
      std::cerr << std::format("connect socket failed\n");
    }
    return false;
  }
  return true;
}

bool SetSockOpt(int fd, int level, int opt_name, const void *opt_val, socklen_t opt_len) {
  if (setsockopt(fd, level, opt_name, opt_val, opt_len) < 0) {
    std::cerr << std::format("setsockopt failed: {}\n", strerror(errno));
    return false;
  }
  return true;
}

bool Bind(int fd, addrinfo *info) {
  if (bind(fd, info->ai_addr, info->ai_addrlen) < 0) {
    const int kBufSize = 100;
    char host_buf[kBufSize]{};
    if (GetNameInfo(info->ai_addr, info->ai_addrlen, host_buf, kBufSize, nullptr, 0, NI_NUMERICHOST)) {
      std::cerr << std::format("bind socket failed({})\n", host_buf);
    } else {
      std::cerr << std::format("bind socket failed\n");
    }
    return false;
  }
  return true;
}

bool Listen(int fd, int listen_num) {
  if (listen(fd, listen_num) < 0) {
    std::cerr << std::format("listen failed: {}\n", strerror(errno));
    return false;
  }
  return true;
}

int OpenClientFd(const char *hostname, const char *port) {
  int client_fd;
  addrinfo hints{
      .ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG,  // Numeric port, Connections
      .ai_socktype = SOCK_STREAM,                  // TCP socket
  };
  addrinfo *info{};
  if (!GetAddrInfo(hostname, port, &hints, &info)) return -2;

  addrinfo *p;
  for (p = info; p; p = p->ai_next) {
    // 1. socket
    client_fd = Socket(p);
    if (client_fd < 0)  {
      std::cout << std::format("skipped\n");
      continue;
    }

    // 2. connect
    if (Connect(client_fd, p)) break;
    std::cout << std::format("skipping and closing\n");
    Close(client_fd);
  }

  freeaddrinfo(info);
  return !p ? -1 : client_fd;
}

int OpenServerFd(const char *port) {
  int server_fd;
  addrinfo hints {
      .ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG | AI_PASSIVE,  // Numeric port, Connections, For bind
      .ai_socktype = SOCK_STREAM,                               // TCP socket
  };
  addrinfo *info;
  if (!GetAddrInfo(nullptr, port, &hints, &info)) return -2;

  addrinfo *p;
  for (p = info; p; p = p->ai_next) {
    // 1. socket
    server_fd = Socket(p);
    if (server_fd < 0) {
      std::cout << std::format("skipped\n");
      continue;
    }

    // SO_REUSEADDR 用于在套接字关闭后立即重用相同的地址
    // 当套接字关闭后, 通常会有一段时间, OS 会保持该地址在用于防止来自同一地址的新连接
    int reuse = 1;
    // 2. 尽量消除 FD INUSE 错误
    SetSockOpt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 3. bind
    if (Bind(server_fd, p)) break;
    std::cout << std::format("skipped\n");
    Close(server_fd);
  }

  freeaddrinfo(info);
  if (!p) return -1;

  // 4. listen
  if (!Listen(server_fd)) {
    Close(server_fd);
    return -1;
  }
  return server_fd;
}

}