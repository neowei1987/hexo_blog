---
title: 双指针-集合交集
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
---

两个集合的交集

（1）排序 + 双指针
（2）hashmap + counter

如果内存放不下如何办？

通过归并外排将两个数组排序后再使用排序双指针查找

最终，集合1和集合2的交集，是x与y与z的并集，即集合{3,5,7,30,50,70}。

画外音：多线程、水平切分都是常见的优化手段。

skiplist 跳表来维护有序结构，搜索引擎如此做
