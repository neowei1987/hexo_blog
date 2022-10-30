---
title: 操作系统 - 物理内存管理
date: 2022-02-25 10:43:03
updated:
mathjax: true
categories:
tags: 
- 操作系统
---

![内存访问](https://pics3.baidu.com/feed/838ba61ea8d3fd1f0c5a12495ab0521794ca5f7c.jpeg?token=dd0db40934355dcfa5bc35bec53f8b4d)

TLB：MMU工作的过程就是查询页表的过程。如果把页表放在内存中查询的时候开销太大，因此为了提高查找效率，专门用一小片访问更快的区域存放地址转换条目。（当页表内容有变化的时候，需要清除TLB，以防止地址映射出错。）

Caches：cpu和内存之间的缓存机制，用于提高访问速率，armv8架构的话上图的caches其实是L2 Cache

### 内存命中率

假设在 n 次内存访问中，出现命中的次数是 m，那么 m / n * 100% 就表示命中率，这是衡量内存管理程序好坏的一个很重要的指标。

如果物理内存不足了，数据会在主存和磁盘之间频繁交换，命中率很低，性能出现急剧下降，我们称这种现象叫**内存颠簸**。这时你会发现系统的 swap 空间利用率开始增高， CPU 利用率中 iowait 占比开始增高。

大多数情况下，只要物理内存够用，页命中率不会非常低，不会出现内存颠簸的情况。因为大多数程序都有一个特点，就是**局部性**。

局部性就是说被引用过一次的存储器位置，很可能在后续再被引用多次；而且在该位置附近的其他位置，也很可能会在后续一段时间内被引用。

### 物理内存管理

![物理内存管理](https://pics7.baidu.com/feed/6609c93d70cf3bc7b0d84842bbfecda9cf112a4e.png?token=4f2dc6e2a73bddf5becd6dd924ebbded)

![Buddy系统](https://pics4.baidu.com/feed/962bd40735fae6cd484f59cc7d4d782c40a70fae.png?token=4296ed176d75fde417a7b04612fe8246)

对于Page级别的内存分配，通过Buddy系统来管理；TCMalloc 也是通过这种方式来管理span。

对于小对象（例如task_struct、mm_struct等）通过SlabAllcator来进行管理分配。这种思路，Memcache会借鉴。
