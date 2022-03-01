---
title: 设计模式-reactor模式
date: 2022-02-18 10:01:03
mathjax: true
categories: 
tags: 
- 设计模式
---

Reactor 模式首先是事件驱动的，有一个或多个并发输入源，有一个Service Handler，有多个Request Handlers；这个Service Handler会同步的将输入的请求（Event）多路复用的分发给相应的Request Handler。如果用图表示的如下：

![Reactor模式](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2019/4/5/169ed823caf32d30~tplv-t2oaga2asx-watermark.awebp)

其实在设计模式层面，IO多路复用也是采用 Reactor 模式的。

IO 多路复用模型可以看成是 Reactor 模式在 IO 模型上的应用。
