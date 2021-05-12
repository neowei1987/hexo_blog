---
title: 常见系统设计题系列-任务调度
date: 2021-01-18 18:36:03
updated:
mathjax: true
categories:
- [系统设计]
tags: 
---

## 单机版本

核心数据结构：堆、时间轮、红黑树

<!-- more -->

触发机制：
如果时间还没有到，client的三种选择：
（1）polling: 定期轮询检查是否有新的任务。缺点在于周期不好确定：太短的话造成CPU使用率过高，太长的话，任务得不到及时处理。
（2）sleep时间差: sleep期间来了一个新的更紧急的任务呢？
（3）锁等待: 多个消费者，如果没有任务则等待；有任务，则leader负责await一段时间；如果来了更紧急的任务，其他线程也会被唤醒。

## 分布式版本

zset + zk watch机制
其中zk watch实现的便是单机版的锁机制；zset则模拟了单机核心数据结构：堆

参考
https://github.com/soulmachine/system-design/blob/master/cn/task-scheduler.md