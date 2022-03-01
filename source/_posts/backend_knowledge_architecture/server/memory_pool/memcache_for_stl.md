---
title: 内存池系列｜STL内存分配
tags: 
- 高性能服务器
- 内存池
---

1. 基于hash的freelist
2. 由于STL知道分配出去的内存对象大小，所以他技巧性地用了union来减少内碎片。
