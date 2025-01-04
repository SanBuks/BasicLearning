#ifndef UTIL_SOCKET_H
#define UTIL_SOCKET_H

#include "netdb.h"

namespace util {

// listen 等待队列最大长度
const constexpr int kListenNum = 1024;

// 从 host:port 获取 addrinfo, 如果出错打印相关信息, 成功返回 true, 失败返回 false
bool GetAddrInfo(const char *host, const char *port, const addrinfo *hints, addrinfo **list);
// 从 sockaddr 获取 host, port 字符串, 如果出错打印相关信息, 成功返回 true, 失败返回 false
bool GetNameInfo(const sockaddr *addr, socklen_t addr_len, char *host_buf, socklen_t host_len,
                 char *port_buf, socklen_t port_len, int flags);

// 创建 socket, 如果出错打印相关信息, 返回 fd
int Socket(addrinfo *info);
// 连接 socket, 如果出错打印相关信息, 成功返回 true, 失败返回 false
bool Connect(int fd, addrinfo *info);
// 设置 socket option, 如果出错打印相关信息, 成功返回 true, 失败返回 false
bool SetSockOpt(int fd, int level, int opt_name, const void *opt_val, socklen_t opt_len);
// 绑定 socket, 如果出现错误打印相关信息, 成功返回 true, 失败返回 false
bool Bind(int fd, addrinfo *info);
// 监听 socket, 如果出现错误打印相关信息, 成功返回 true, 失败返回 false
bool Listen(int fd, int listen_num = kListenNum);

// 打开客户端
int OpenClientFd(const char *hostname, const char *port);
// 打开服务端
int OpenServerFd(const char *port);

}
#endif
