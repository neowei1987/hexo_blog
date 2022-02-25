---
title: 常见系统设计题系列- 带TTL的KV存储
date: 2021-01-19 15:48:03
updated:
mathjax: true
categories:
- [系统设计]
tags: 
---

设计一个带有有效时间TTL的KV存储系统，包含set（key，value，ttl）、get（key）方法、怎么优化

首先是KV存储，可以使用levelDB作为我们的存储引擎；

另外，需要考虑数据的复制与分片、去中心化等

把TTL当作value，当进行compaction时，过期的数据会被忽略。
