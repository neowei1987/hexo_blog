---
title: 高性能服务器设计-常见IO多路复用技术介绍
date: 2022-02-18 10:01:03
mathjax: true
categories:
- 
tags: 
- 
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
3. 使用mmap加速内核与用户空间的消息传递
4. 更丰富的触发方式，同时支持水平触发（LT)与边缘触发（ET)