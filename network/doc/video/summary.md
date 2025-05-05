# 1-1: A day in the life of an application
## 字节流模型
- 可靠的, 双向, 字节流
- 两个程序通过网络建立通讯的模型, 可以由任意一端关闭
- 优点: 抽象整个网络功能

## 不同例子
- HTTP: 超文本传输协议
  - 输入网页地址, 浏览器与服务器建立连接
  - 发送 GET 请求
  - 获取回应
- BitTorrent: 
  - 文件被分为多个数据段(Pieces) 
  - 集群(Swarm): 分布式的客户端, 可以互相分享数据段
  - Torrent: 记录 Tracker 服务器信息
  - Tracker: 用户通过 HTTP 获取集群信息, 分别建立连接, 监听客户端的加入和离开并及时通知
- Skype: NAT(Network Address Translator)
  - 红绿屏障(类似二极管, 可以从绿色端建立连接, 反向不可以) 
  - Rendezvous(约会服务器) 解决一端处于 NAT 后问题: (A->B)
    - B 预先连接中继 
    - A 主动连接中继
    - 中继提示 B, B 主动连接 A
  - Relay(中继服务器) 解决两端处于 NAT 后问题: 
    - Relay 转发
    - A 与 B 主动连接 Relay

# 1-2: The four layer Internet model
- 4 层模型: 模块化, 按照依赖分层, 方便复用
- 物理层(physic):
  - 作用: 将帧的每个比特传输到下一个节点 
  - 特点: 协议与链路层和实际传输媒介相关
- 链路层(link): 帧(frames)
  - 作用: 通过链路传送帧, 逐一段(hop by hop)链路(主机/路由)传递分组信息(packet), 传输地点由帧内容指定
  - 协议: WiFi / Ethernet / 5G 
  - 特点: 具体实现不同
- 网络层(network): 数据报(datagram)
  - 作用: 主机到主机传送数据报(指定传输路线, 传输不可靠数据)
  - 协议: IP协议(Thin Waist), 包括路由选择协议, 网际协议
  - 特点: 最大努力传递但不保证正确, 可能存在丢失/乱序/破坏
- 传输层(transport): 报文段(segment)
  - 作用: 程序端到端传递报文段(向应用层提供可靠传输)
  - TCP协议(Transmit Control Protocol): 面向连接, 确保正确且有序, 流量控制, 拥塞控制
  - UDP协议(User Datagram Protocol): 无连接, 无可靠性, 无流量控制, 无拥塞控制
- 应用层(app): 报文(message)
  - 作用: 定义信息交流语义, 建立字节流模型
  - 协议: HTTP等

# 1-3: The IP service model 
- 数据报: `[IP-data | IP-hdr(SA | DA)] -> [link-frame data | link-frame hdr] (divided packets)`
- 传递方式: packets, hop-by-hop, routing
- 特点: 分组数据报, 不可靠, 最大努力传递, 无连接(建立或断开没有相关状态)
- 设计的原因:
  - 成本低: 设备使用广泛需要降低成本
  - 端到端原则: 复杂的, 可实现的特性尽量在端处实现, 连接部分尽可能简单
  - 保留可拓展性: 比如允许可靠和不可靠传输构建
  - 对于链路层的要求少: 作用于任何一个链路层
- 细节:  
  - TTL(time to live)机制, 防止跳转循环
  - 拆分数据报, 端点提供重新组装能力
  - 头部校验减少传错目的地的可能性
  - IPv4(32bit), IPv6(128bit)
  - 允许添加新的字段
- IPv4 datagram 构成:
-----------------------------------------------------
  - Version(4): IP版本号
  - Header Length(4): 头部长度(提示存在额外字段) 
  - Type of Service(8): 提示路由重要性
  - Total Packet Length(16): 整体数据报长度(包含头部)
-----------------------------------------------------
  - Packet ID(16): 分段
  - Flags(4): 分段
  - Fragment Offset(12): 分段
-----------------------------------------------------
  - TTL(8): 防止循环
  - Protocol ID(8): 传输层所属协议类型(IADA机构分配)
  - Checksum(16): 校验和, 头部计算出来, 防止地点错误
-----------------------------------------------------
  - SA(32): 源地址 
-----------------------------------------------------
  - DA(32): 目标地址
-----------------------------------------------------
  - DATA  
-----------------------------------------------------

# 1-4: A Day in the Life of a Packet
- TCP byte stream:
  - 三次握手: SYN, SYN/ACK, ACK 
  - IP address: 哪个端点
  - TCP port: 哪个程序 (Webserver 80)
- WireShark: tcp.port == 443 && ip.addr == 128.148.32.12
- `$tracerout -w 1 www.cs.brown.edu`

# 1-5: Packet switching principle
- packet: 自足数据单元, 携带目的地址必要信息
- stream: 所属同一 端到端 连接的有序数据报的集合
- 数据包交换: 路由对于每个接收的数据包, 单独通过跳转表选择链路进行传输, 如果链路占用则等待
- 作用: 
  - 路由不需要知道数据包状态, 流的状态, 只进行简单跳转 
  - 数据传输具有突发性, 路由的转发资源可以随着实际使用状况有效共享(统计复用)

# 1-6: Layering principle"
- 模块化, 可复用, 明确服务(API), 分离关注点(解耦), 可拓展
- 层与层之间逻辑上建立"连接

# 1-7: Encapslation principle
- 封装结构:
  - link header - network header - transmit header 
  - data
  - transmit footer - network footer - link footer
- TLS:
  - 递归改变封装层次 
  - TLS (IP datagram) 作为 application-data 封装在 指向 VPN 服务器 Datagram 中

# 1-8: byte order
- 小端: LSB MSB, 大端: MSB LSB, 网络用大端序
- htons, htonl (host -> net short/long)
- ntohs, ntohl (new -> host short/long)
- IPv4 Total Length 2Byte 大端

# 1-9: IPv4 addresses
- net_mask & ip1 == net_mask & ip2: 标识机器是否在同一个网络上, 在则数据包不需要通过 IP 路由
- ifconfig(interface config)
  - en：以太网接口（Ethernet Interface）
  - fw：FireWire 接口（FireWire Interface）
  - p2p：点对点接口（Point-to-Point Interface）
  - lo：本地回环接口（Loopback Interface）
  - utun：虚拟私有网络接口（Virtual Private Network Interface） 
  - stf0：6to4 Interface（6to4 接口）的标识符
  - gif0：Generic Tunnel Interface（通用隧道接口）的标识
- class: 先导位 + 管理域(network) + 管理域中的设备(host)
  - A: 0 / 7 / 24  
  - B: 10 / 14 / 16
  - C: 110 / 21 / 8
  - Classless Inter Domain Routing (CIDR): 171.64.00/16 = 171.64.0.0 - 171.64.255.255
- IANA 分配 /8 给 RIRs 机构

# 1-10: Longest prefix match
- 跳转表由 CIDR 构成: 掩码标识精确匹配位数
  - 0.0.0.0/0     default 
  - 172.1.0.0/16  no.1 link
  - 172.1.3.0/24  no.2 link
  - 172.0.0.0/8   no.3 link

# 1-11: ARP
- Address Resolution Protocol: 处理 IP 网络层地址 -> 链路层设备地址映射(如以太网网卡地址 48位)
- Host 可能有多个 IP 地址, 举例: 网关有两个 interface 连接不同网络, 如果只有一个无法通过掩码标识不同网络域
- ARP: 
  - 简单 request-reply 机制
  - 收到请求的节点会广播请求
  - 回复不会广播只会回复致对应节点(最初的规定, 现在可以广播)
  - 节点可以发送不存在的请求来宣传自己的信息
  - packet 有冗余数据, 广播的过程中会插入或更新缓存
  - 节点保存映射缓存保存时间 20分钟致不等
- ARP 结构:  
```
- hardware | protocol
- hardware len |  protocol len | Opcode
- src hardware address 
- src ip address
- dest hardware address 
- dest ip address
- data

- 1(eth) | 8(ip)
- 6 | 4 | 1(request)
- 68:A8:6D:05:85:22
- 192.168.0.5
- FF:FF:FF:FF:FF:FF(broadcast)
- 192.168.0.1

- 1(eth) | 8(ip)
- 6 | 4 | 2(reply)
- 00:18:E7:F3:CE:1A
- 192.168.0.1
- 68:A8:6D:05:85:22
- 192.168.0.5
```

# 2-1 TCP service model
- 
