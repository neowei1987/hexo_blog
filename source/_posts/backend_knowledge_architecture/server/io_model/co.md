---
title: 协程
date: 2022-12-16 23:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---

## 0. 协程优缺点

协程是使用同步的编程思想，达到异步的效率

核心点：

1.使用异步IO未就绪，就切换到已经准备就绪的IO去操作
解决了异步代码逻辑复杂，同步效率低的问题，效率接近异步

2.协程的栈可以设置比线程更小，使得更加容易

解决了线程占用栈空间更大的问题，硬件的使用率更高，同异步的效率，硬件成本会更低

3.线程的创建代价和调度代价相对比较高

缺点 ：

1. 缺点是无法利用多核资源，本质是单核的，它不能同时将单个CPU的多个核用上，协程需要和进程配合才能运行在多CPU上。
2. 跨平台性挑战较大

<!-- more -->

有栈协程 与 无栈协程

这篇文章可以看看
https://www.zhihu.com/question/568012609/answer/2768851451

参考：

https://zhuanlan.zhihu.com/p/330606651
https://blog.csdn.net/carlclouder/article/details/126048486