---
title: 消息队列-Kafka
date: 2022-02-25 13:06:03
mathjax: true
categories:
- 
tags: 
- 
---

![设计思想](https://img-blog.csdn.net/20180317011215184?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

#### cosume group

通过cosume group，巧妙的解决了广播问题。

#### 高性能

SendFile、zero copy

#### 索引设计

Kafka为了卸载MQ本身的复杂性，为了其**真正无状态**的设计，它将状态维护机制这口锅完全甩给了消费者，因此取消息的问题就转化成了**消费者拿着一个offset索引来Kafka存储器里取消息**的问题，这就涉及到了性能。But 如何能查的更快？How？

![扫描partition文件](https://img-blog.csdn.net/20180317015646335?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

但实际上，

![partition](https://img-blog.csdn.net/20180317020648952?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

1. partition并不是一根文件，而是一个目录
2. 目录下面存了很多逻辑上的segment，每一个segment物理上包括两个文件：索引文件、日志文件（每次都append)

文件的命名相当于查找的稀疏索引，省去索引文件

每个segment索引又是一个稀疏索引减少索引文件的大小

#### replication

ISR数据同步、ACK选项（全部ack、只有一个ack）

参考：

https://blog.csdn.net/dog250/article/details/79588437