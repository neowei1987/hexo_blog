---
title: 跳表
date: 2022-03-01 14:00:03
mathjax: true
categories:
tags: 
---

skiplist 并发性能好一些

https://segmentfault.com/a/1190000020596941

跳表：改变索引构建策略，有效平衡执行效率与内存消耗

随机化思想：
跳表是一种随机化数据结构，其随机化体现在插入元素的时候元素所占有的层数完全是随机的，层数是通过随机算法产生的:

使用场景：
Redis ZSET实现

LevelDB

LevelDB选用SkipList一来和SkipList的高效、简洁相关，二来SkipList也仅存在MemTable一种简单应用场景