---
title: 高性能服务器设计-常见IO多路复用技术介绍
date: 2022-02-18 10:01:03
mathjax: true
categories:
- 
tags: 
- 高性能服务器
---

## select

不足：

1. 通过数组来管理fd，数量限制
2. 触发方式单一，仅支持水平触发（LT)

## poll

优点：通过链条来管理fd，突破数量限制

不足：

1. 当你拥有一个很大的socket集合，不过由于网络延时，任一时间只有部分socket是“活跃”的，但是select/poll每次调用都会线性扫描全部的集合（时间复杂度是$O(n)$，导致效率呈线性下降。
2. 内核与用户态的数据拷贝

## epoll

特点：

1. 没有最大并发连接的限制
2. 通过红黑树管理所有的fd，时间复杂度为$O(lgn)$
3. 更丰富的触发方式，同时支持水平触发（LT)与边缘触发（ET)

---

Reactor模型

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.2mm6jjukluo0.webp)

单线程Reactor模型
优点：单 Reactor 单进程的方案因为全部工作都在同一个进程内完成，所以实现起来比较简单，不需要考虑进程间通信，也不用担心多进程竞争。
不足：
（1）第一个缺点，因为只有一个进程，无法充分利用 多核 CPU 的性能；【该缺点可以部署多个进程来解决】
（2）第二个缺点，Handler 对象在业务处理时，整个进程是无法处理其他连接的事件的，如果业务处理耗时比较长，那么就造成响应的延迟；
使用场景：CPU密集型
例子：Redis

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.4ifee5h5pqm0.webp)

单 Reactor 多线程 / 多进程
优点：能够充分利用多核CPU
不足：
（1）子线程完成业务处理后，要把结果传递给主线程的 Reactor 进行发送，这里涉及共享数据的竞争。
（2）因为一个 Reactor 对象承担所有事件的监听和响应，而且只在主线程中运行，在面对瞬间高并发的场景时，容易成为性能的瓶颈的地方。
使用场景：
例子：?

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.45unud2y5380.webp)

多 Reactor 多线程 / 多进程
优点：克服单 Reactor 多线程 / 多进程的缺点2，主线程不会成为瓶颈；【相对上面的方案，实现更加简单一些】主线程和子线程分工明确，主线程只负责接收新连接，子线程负责完成后续的业务处理；主线程和子线程的交互很简单，主线程只需要把新连接传给子线程，子线程无须返回数据，直接就可以在子线程将处理结果发送给客户端。
不足：
使用场景：
例子：memcache、Netty

多 Reactor 多线程 / 多进程（变种）
思路：进一步的放大子线程/子进程的工作，把accept的工作也交给了子进程。
使用场景：
例子：Nginx
