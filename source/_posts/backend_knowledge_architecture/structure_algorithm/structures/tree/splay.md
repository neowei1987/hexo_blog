---
title:  Splay Tree
date: 2022-03-01 13:44:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

SplayTree，一种二叉查询树，与红黑树类似，是一种自调整的二叉树，

但是调整过程不仅仅发生在插入和删除，SplayTree中对节点访问都是通过splay操作完成节点的定位，查询、插入都是通过splay操作得到节点位置，每个splay操作都将进行对节点进行调整，将目标节点调整至树根，频繁访问的节点，调整到离根近的位置上，加快查询速度，反之“冷”节点的查询会耗时多。

按照8-2原则，假如程序80%的查询量中，频繁被查询到的数据仅仅是总数据的20%，那么将数据放入SplayTree中提供查询，对“热”数据的查询会大大加速，这样子会大大降低这80%查询量所需要的时间。

事物总有其缺陷的一面，SplayTree也是如此，倘若访问“冷”节点，这时的代价可能是O(n)，但是对于“热”节点，甚至可以达到O(1)。

Squid中SplayTree应用于ACL，所谓ACL即访问控制列表，用户通过配置文件配置的ACL元素(例如：http_accessacl1,acl2,acl3，这里的acl1，acl2，acl3就是acl元素)，在内存中使用两种方式组织，一种是SplayTree，另一种是链表。采用的SplayTree组织ACL的种类有：DSTIP、SRCIP、用户认证、DSTDOMAIN等，原因很简单，这些元素访问非常频繁，假如元素很多时，链表查询的代价是O(n)，让这些类型ACL元素放入SplayTree中，那么查询时间就是可以做到O(log(n))，甚至是O

理论依据：局部性原理

参考：
http://blog.csdn.net/yykxx/article/details/8679017