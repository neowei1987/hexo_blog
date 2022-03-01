---
title: MC缓存必知必会
date: 2022-02-16 23:20:03
updated:
mathjax: true
categories:
tags: 
- 缓存
---

memcached作为高速运行的分布式缓存服务器，具有以下的特点:

协议简单，文本协议

基于libevent的事件处理，对服务器的连接数增加，也能发挥O(1)的性能

操作：
（1）set， get， del
（2）多key查询
（3）原子自增，自减

### memcache内存分配

Slab Allocator的基本原理是按照预先规定的大小，将分配的内存分割成特定长度的块，以完全解决内存碎片问题。
但是存在内存浪费问题！！

### memcache删除机制

基于LRU(Least Recently Used)算法自动删除不使用的缓存

Lazy Expiration

memcached内部不会监视记录是否过期，而是在get时查看记录的时间戳，检查记录是否过期。这种技术被称为lazy（惰性）expiration。因此，memcached不会在过期监视上耗费CPU时间。

## 哈希算法

memcached不互相通信的分布式，由客户端来实现

### 根据余数计算分散

数据的分散性也相当优秀，但也有其缺点。那就是当添加或移除服务器时，缓存重组的代价相当巨大。
添加服务器后，余数就会产生巨变，这样就无法获取与保存时相同的服务器，从而影响缓存的命中率。

### 一致性Hash

但Consistent Hashing中，只有在continuum上增加服务器的地点逆时针方向的第一台服务器上的键会受到影响。Consistent Hashing最大限度地抑制了键的重新分布。

而且，有的Consistent Hashing的实现方法还采用了虚拟节点的思想。使用一般的hash函数的话，服务器的映射地点的分布非常不均匀。

因此，使用虚拟节点的思想，为每个物理节点（服务器）在continuum上分配100～200个点。这样就能抑制分布不均匀，最大限度地减小服务器增减时的缓存重新分布。

### hash表扩容

基于双缓冲思想的扩容方案

启动一个后台线程，监控hash表大小，如果快满了，则拷贝到新的hash表【扩大容量】
