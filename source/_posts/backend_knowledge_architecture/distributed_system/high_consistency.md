---
title: 分布式系统-一致性
date: 2022-2-23
tags:
---

#### CAP VS BASE

#### 一致性

##### 强一致性

保证手段：单机落磁盘、数据库事务、分布式事务等

##### 弱一致性

可能丢失一定的数据：异步复制、PageCache的write back

##### 最终一致性

带TTL的缓存