## 环境配置(Ubuntu 23.10)
```bash
$ sudo apt update
$ sudo apt install git cmake gdb 
$ sudo apt install clang clang-tidy clang-format 
$ sudo apt install clang clang-tidy clang-format 
$ sudo apt install build-essential gcc-doc pkg-config glibc-doc tcpdump tshark 
```

## telnet
- telnet: 允许用户通过命令行界面远程访问和管理计算机, 明文方式传输数据
- $telnet cs144.keithw.org http 与主机 cs144.keithw.org 通过 HTTP 服务, 建立可靠字节流
- telnet 退出
```bash
$ telnet cs144.keithw.org http
Trying 104.196.238.229...
Connected to cs144.keithw.org.
Escape character is '^]'.
^]
telnet> close
Connection closed.
```
- telnet HTTP 请求
```bash
$ telnet cs144.keithw.org http
Trying 104.196.238.229...
Connected to cs144.keithw.org.
Escape character is '^]'.
GET /hello HTTP/1.1
Host: cs144.keithw.org
Connection: close

HTTP/1.1 200 OK
Date: Sat, 04 Jan 2025 08:24:28 GMT
Server: Apache
Last-Modified: Thu, 13 Dec 2018 15:45:29 GMT
ETag: "e-57ce93446cb64"
Accept-Ranges: bytes
Content-Length: 14
Connection: close
Content-Type: text/plain

Hello, CS144!
Connection closed by foreign host.
```

## netcat  
$ netcat -lvnp 9091 
  - -l：监听模式
  - -v：启用详细模式
  - -n：不用 DNS, 直接使用 IP 地址
  - -p：监听端口号
$ telnet localhost 9091 与端口建立连接

## webget
- 系统内核提供 stream socket 建立可靠字节流
- 网络提供 最大努力 交付 数据包
 - headers
 - source 
 - destination 
 - payload data
- 存在问题 
 - lost
 - delivered out of order
 - delivered with the contents altered
 - duplicated 
- 操作系统或终端需要将 最大努力交付数据包转化成 可靠字节流 通过 TCP(Transmission Control Protocol) 协议
  - HTTP 每行 \r\n 结尾
  - 服务器关闭会立刻发送回应提示关闭
  - socket.eof() 判断是否结束

## util
- CheckSystemCall(s_attempt, return_value) 系包装统调用函数, 抛出异常
- FileDescriptor 文件描述符包装类
 - std::shared_ptr<FDWrapper> internal_fd_;
 - iovecs 多缓冲区读写
- FDWrapper
 - int fd_;                    // The file descriptor number
 - bool eof_ = false;          // indicating fd_ is at EOF
 - bool closed_ = false;       // indicating fd_ has been closed
 - bool non_blocking_ = false; // indicating fd_ is non-blocking
 - fcntl(fd, opt) 获取标志位判断是否是阻塞
- TCPSocket 
 - socket(domain, type, protocol)
 - shutdown(fd, opt)  
  - SHUT_RD   = No more receptions;
  - SHUT_WR   = No more transmissions;
  - SHUT_RDWR = No more receptions or transmissions.

## in-memory reliable byte stream
- 字节流, 读写各两端
- 读会读到末尾 EOF
- 写会存在写容量上限
- 字节流长度可以任意长度, 即使容量有限
- ring-buffer