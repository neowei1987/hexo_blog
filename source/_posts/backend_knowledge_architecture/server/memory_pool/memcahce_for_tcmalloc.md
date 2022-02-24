---
title: 内存池系列｜TCMalloc分析
---

实现要点

1. 分层（ThreadCache, CentralCache, PageCache)
2. 线程局部存储来管理ThreadCache
3. 通过基于hash的freelist来管理小对象
4. 通过radix tree来管理分配出来的obj到span的映射，如此来方便做回收。
5. 通过buddy算法来管理span, 保证用来分配内存的span尽可能的大（大的**总是**可以通过分裂成为小的，小的只有在**合适的时机-内存连续**才能合并成为大的）
