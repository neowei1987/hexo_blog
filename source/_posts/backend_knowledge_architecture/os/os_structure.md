---
title: 操作系统中碰到的数据结构汇总
date: 2022-02-25 10:35:03
updated:
mathjax: true
categories:
tags: 
- 操作系统
- 数据结构
---

#### hash

hlist_head hlist_node 散列表拉链

根据PID定位task：PID哈希表

#### 双向链表

list_head 双向链表

提高调度程序运行速度：建立多个可运行程序链表

等待队列（双向链表）：用自旋锁加保护的等待队列头、等待队列链表的元素

等待队列中睡眠进程的唤醒：互斥进程，非互斥进程

链表维护节点；节点包括管理区【硬件限制，ZONE_DMA, ZONE_NORMAL, ZONE_HIGHMEM】+ page数组

动态定时器的链表组（将同一时间段内即将到时的定时器归入一组）

#### bitmap

pid分配管理：bitmap pidmap_array

inode、磁盘文件数据块

#### 并发与同步

##### 每CPU变量

不需要同步的内核数组，为每个cpu分配数组一元素

##### 自旋锁

##### RCU机制

RCU(读取-拷贝-更新)：只保护被动态分配并通过指针引用的数据结构

何时释放旧副本？ CPU经过静止状态后，定期检测！！

#### 原子变量

#### 其他

thread 与 thread_info 紧密挨着；根据esp 屏蔽 低13位 可以最快的获取thread_info;
同时进程描述符指针在thread_info中的偏移为0!

也就是将： OS将task_struct指针存放到了栈上（可以通过esp做简单的AND操作即可）

jiffies:子系统启动的节拍总数
