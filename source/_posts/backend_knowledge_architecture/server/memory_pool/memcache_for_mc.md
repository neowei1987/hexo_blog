---
title: 内存池系列｜MC内存分配
tags: 
- 高性能服务器
- 内存池
---

slab allcator的机制

![memcache内存分配示意图](http://cdn.b5mang.com/2021320115717.png)

综合上面的介绍，memcached的内存分配策略就是：按slab需求分配page，各slab按需使用chunk存储。

这里有几个特点要注意，

Memcached分配出去的page不会被回收或者重新分配

Memcached申请的内存不会被释放

slab空闲的chunk不会借给任何其他slab使用
