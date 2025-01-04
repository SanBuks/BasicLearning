#include <sys/types.h>
#include <sys/socket.h>

// socket 连接过程
// client:            server:
// getaddrinfo        getaddrinfo
// socket             socket
//                    bind
//                    listen
//--------------------------------
// connect            accept
// ...                ...
// close              close

int main() {


  auto fd = socket(AF_INET, SOCK_STREAM, 0);


  return 0;
}