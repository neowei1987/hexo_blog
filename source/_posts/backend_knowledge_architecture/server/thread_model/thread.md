---
title: 高性能服务器设计-常见线程模型
date: 2022-02-18 10:01:03
mathjax: true
categories:
- 
tags: 
- 高性能服务器
---

### 单线程模型

代表：Redis

基本原理：

单一线程，依次socket->bind->listen，然后epoll_wait分别进行accept以及读写事件

优点&使用场景：

简单、没有并发锁问题；适用于短耗时的计算密集型服务

缺点：

不能支持耗时较长的事件，尤其是IO密集型

### 单线程(listen+accept+epoll_wait) + 1队列通知 + n线程(读写处理) 模型

代表：thrift-nonblocking-server

基本原理：

1. 在这种模型中，有1+n个线程
2. 有1个线程执行端口的listen并把listen_fd加入该线程的epoll_set，然后循环去做如下事情：

    2.1 epoll_wait监听新连接的到

    2.2 调用accept获得新到的fd

    2.3 把fd放入队列

    回到2.1，继续epoll_wait

3. 另外有n个工作线程，从队列里面获取文件描述符，然后执行：1）读取数据，2）执行任务

优点：

- 模型不算复杂
- 并发能力强，能够充分利用多核
- 天然支持负载均衡（每个工作工作线程完成任务之后就会去队列里主动获取文件描述符）

缺点：

队列可能是性能瓶颈，尤其是当业务逻辑耗时本身极其短的情况下

### 单线程(listen+accept+epoll_wait) + n队列通知 + n线程(读写处理) 模型

代表：memcache

基本原理：

- 这种模型基本类似于上一种模型，区别在于把1个队列换成n个队列，每个工作线程绑定一个队列，每个工作线程从自己的队列消费数据，其他的保持一致

- LISTEN线程往PIPE里写入一个哨兵，通知WORKER线程队列可读

优点：

并发能力更强。相比于单队列的模型，多队列的好处是减少了队列的锁竞争。对于短耗时任务能得到比较多的提升，很适合缓存类应用

缺点：

有可能导致负载不均。因为监听线程是不会去根据不同线程的处理速度决定把任务分配给哪个线程的，如果每个任务的耗时不均衡，那么就可能导致有些线程累死，有些线程饿死。

单线程listen, 在处理高速率海量连接时，单线程可能会成为瓶颈

### 单进程(listen) + n进程(accept + epoll + 读写处理) 模型

代表：nginx

基本原理：

1. master进程监听新连接的到来，并让其中一个worker进程accept。这里需要处理惊群效应问题(加锁、SO_REUSEPORT)
2. worker进程accept到fd之后，把fd注册到到本进程的epoll句柄里面，由本进程处理这个fd的后续读写事件
3. worker进程根据自身负载情况，选择性地不去accept新fd，从而实现负载均衡

### 单线程(listen) + n线程(accept + epoll + 读写处理 + 协程) 模型
