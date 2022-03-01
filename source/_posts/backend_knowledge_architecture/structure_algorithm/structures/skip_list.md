---
title: 跳表
date: 2022-03-01 14:00:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
---


跳表是一种随机化数据结构，

其随机化体现在插入元素的时候元素所占有的层数完全是随机的，层数是通过随机算法(随机化思想)产生的。

改变索引构建策略，有效平衡执行效率与内存消耗

使用场景：

1. Redis ZSET实现
2. LevelDB选用SkipList来实现memory table

参考：https://segmentfault.com/a/1190000020596941