#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <format>
#include <iostream>

//  Structure to contain information about address of a service provider.
//  struct addrinfo {
//    int ai_flags;              // Input flags.
//    int ai_family;             // Protocol family for socket.
//    int ai_socktype;           // Socket type.
//    int ai_protocol;           // Protocol for socket.
//    socklen_t ai_addrlen;      // Length of socket address.
//    struct sockaddr *ai_addr;  // Socket address for socket.
//    char *ai_canonname;        // Canonical name for service location.
//    struct addrinfo *ai_next;  // Pointer to next in list.
//  };

const int kBufSize = 100;
char host_buf[kBufSize]{};
char service_buf[kBufSize]{};

int main() {
  const char *hostname = "www.baidu.com";
  const char *service = "http";

  // 默认初始化替换 memset(&hints, 0, sizeof(hints))
  struct addrinfo hints{
      .ai_family = AF_INET,        // 支持 IPv4 和 IPv6
      .ai_socktype = SOCK_STREAM,  // TCP socket
  };

  addrinfo *results;
  addrinfo *p;
  int status;

  if ((status = getaddrinfo(hostname, service, &hints, &results)) != 0) {
    std::cout << std::format("getaddrinfo error: {}\n", gai_strerror(status));
    return 1;
  }

  for (p = results; p; p = p->ai_next) {
    char ipstr[INET_ADDRSTRLEN];

    auto *ipv4 = (struct sockaddr_in *) p->ai_addr;
    auto addr = &(ipv4->sin_addr);
    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
    std::cout << std::format("{}://{} IP address: {}\n", service, hostname, ipstr);

    if ((status = getnameinfo(p->ai_addr, p->ai_addrlen,
                              host_buf, kBufSize,
                              service_buf, kBufSize,
                              NI_NUMERICHOST) != 0)) {
      std::cout << std::format("getnameinfo error: {}\n", status);
      continue;
    }
    std::cout << std::format("{}://{}\n", service_buf, host_buf);
    std::cout << "\n";
  }

  freeaddrinfo(results);
  return 0;
}
