#include <arpa/inet.h>

#include <format>
#include <iostream>

//  Structure describing a generic socket address
//  struct sockaddr
//  {
//    unsigned short int sa_family;	// Common data: address family and length
//    char sa_data[14];	            // Address data
//  };

//  Structure describing an Internet socket address
//  struct sockaddr_in {
//    unsigned short int sin_family;  // socket internet address family:
//                                    // AF_INET(IPv4), AF_INET6(IPv6), AF_UNIX(UNIX 域)
//    uint16_t sin_port;			  // port number
//    struct in_addr sin_addr;		  // internet address
//    unsigned char sin_zero[8];      // Pad to size of `struct sockaddr'
//  }

int main() {
  sockaddr_in addr{};

  std::cout << std::format("sizeof sockaddr: {}\n", sizeof(sockaddr));
  std::cout << std::format("sizeof sockaddr_in: {}\n", sizeof(addr));

  std::cout << std::format("sizeof sockaddr_in.sin_family: {}\n", sizeof(addr.sin_family));
  std::cout << std::format("sizeof sockaddr_in.sin_port: {}\n", sizeof(addr.sin_port));
  std::cout << std::format("sizeof sockaddr_in.sin_addr: {}\n", sizeof(addr.sin_addr));
  std::cout << std::format("sizeof sockaddr_in.sin_zero: {}\n", sizeof(addr.sin_zero));

  return 0;
}