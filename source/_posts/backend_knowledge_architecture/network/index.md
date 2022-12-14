---
title: 计算机网络必知必会
date: 2022-02-16 23:20:03
updated: 
mathjax: true 
categories: 
tags: 
- 计算机网络
---


-------User-----

application    write(fd,buf.len)

-------Kernel-----

File        Validate file descriptor.
Sockets     Copy/append buf to **socket buffer**.
TCP         Create TCP segment according to TCP state, Compute checksum.
IP          Add IP header,perform IP routing. Compute checksum.
Ethernet    Add Ethernet header,perform ARP.
Driver      Tell NIC to send the packet.

-------Device-----
NIC        Fetch the packet from host memory and send it. Interrupt the host when send is done.

缓冲区被塞满

如图所示，物理介质上的数据帧到达后首先由NIC（网络适配器）读取，写入设备内部缓冲区Ring Buffer中，再由中断处理程序触发Softirq从中消费，Ring Buffer的大小因网卡设备而异。当网络数据包到达（生产）的速率快于内核处理（消费）的速率时，Ring Buffer很快会被填满，新来的数据包将被丢弃；

报文mac地址丢包

一般计算机网卡都工作在非混杂模式下，此时网卡只接受来自网络端口的目的地址指向自己的数据，如果报文的目的mac地址不是对端的接口的mac地址，一般都会丢包，一般这种情况很有可能是源端设置静态arp表项或者动态学习的arp表项没有及时更新，但目的端mac地址已发生变化（换了网卡），没有更新通知到源端（比如更新报文被丢失，中间交换机异常等情况）；

## 长链接 VS 短链接

长连接：

长连接多用于操作频繁，点对点的通讯（尤其是需要下行消息的场景，例如**即时通信**），而且连接数不能太多的情况。

短连接：

web网站的http服务一般都用短连接。因为长连接对于服务器来说要耗费一定的资源。

像web网站这么频繁的成千上万甚至上亿客户端的连接用短连接更省一些资源。试想如果都用长连接，而且同时用成千上万的用户，每个用户都占有一个连接的话，可想而知服务器的压力有多大。所以并发量大，但是每个用户又不需频繁操作的情况下需要短连接。

## TCP与UDP的区别

流模式 VS 数据报模式、连接 VS 无连接、可靠性

### TCP与UDP应用

TCP:对效率要求低，对准确性要求较高 (如文件传输、重要状态的更新等)

eg.  STMP, TELNET, HTTP, FTP

UDP:对效率要求高，对准确性要求较低 (如视频传输、实时通信等)。

eg.  DNS,TFTP,RIP,DHCP,SNMP
