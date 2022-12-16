---
title: 惊群现象
date: 2022-12-16 22:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---

A、accept 惊群
以多进程为例，在主进程创建监听描述符listenfd后，fork()多个子进程，多个进程共享listenfd，accept是在每个子进程中，当一个新连接来的时候，会发生惊群。

在内核2.6之前，所有进程accept都会惊醒，但只有一个可以accept成功，其他返回EGAIN。

在内核2.6及之后，解决了惊群问题，办法是在内核中增加了一个互斥等待变量。一个互斥等待的行为与睡眠基本类似，主要的不同点在于：
a）当一个等待队列入口有 WQ_FLAG_EXCLUSEVE 标志置位, 它被添加到等待队列的尾部。若没有这个标志的入口项，则添加到队首。

b）当wake up被在一个等待队列上调用时,它在唤醒第一个有 WQ_FLAG_EXCLUSIVE 标志的进程后停止。
执行步骤：
对于互斥等待的行为，比如对一个 listen 后的socket描述符，多线程阻塞 accept 时，系统内核只会唤醒所有正在等待此时间的队列的第一个，队列中的其他人则继续等待下一次事件的发生。这样就避免的多个线程同时监听同一个socket描述符时的惊群问题。

B、epoll惊群
epoll惊群分两种：

a)是在fork之前创建 epollfd，所有进程共用一个epoll。

b)是在fork之后创建 epollfd，每个进程独用一个epoll。

a)fork之前创建epollfd(新版内核已解决)

主进程创建 listenfd，创建epollfd;

主进程 fork多个子进程;

每个子进程把listenfd，加到epollfd 中。

当一个连接进来时，会触发epoll惊群，多个子进程的epoll同时会触发。

这里的epoll惊群跟 accept 惊群是类似的，共享一个 epollfd，加锁或标记解决，在新版本的epoll中已解决，但在内核2.6及之前是存在的。

b)fork之后创建epollfd(内核未解决)

主进程创建 listendfd;

主进程创建多个子进程;

每个子进程创建自已的epollfd;

每个子进程把listenfd加入到epollfd中;

当一个连接进来时，会触发epoll 惊群，多个子进程epoll同时会触发。

因为每个子进程的epoll是不同的epoll, 虽然listenfd是同一个，但新连接过来时,accept会触发惊群。因为内核不知道该发给哪个监听进程，因为不是同一个epoll。所以这种惊群内核并没有处理，惊群还是会出现。
————————————————
版权声明：本文为CSDN博主「84岁带头冲锋」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/L2111533547/article/details/125982204