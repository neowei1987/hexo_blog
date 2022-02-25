---
title: 高性能服务器系列-libsvrkit RPC框架
---

1. 同时只有一个worker来accept接受新的连接请求。一个连接上的所有请求都是由同一个worker来处理。

2. 通过iovec来接收输入, iovec可以直接交给pb来解析。

3. 如果是一个新的请求包，则开启一个co由它来进行处理。

4. 如果是一个回复包，则根据回复包的seqno, 查询map， 找到对应的co， co_resume， 执行原来的业务逻辑。

5. 通过时间轮来管理所有的超时时间。

6. epoll_wait的timeout 是 min(1ms, 下次超时时间)

7. 通过pipe来进行线程同步。
