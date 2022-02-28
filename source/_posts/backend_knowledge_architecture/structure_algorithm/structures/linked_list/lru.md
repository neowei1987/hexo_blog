---
title: 链表系列-LRU缓存
date: 2022-02-28 21:40:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
- 哈希
---

什么是LRU缓存，怎么设计的LRU缓存。
时间复杂度：$O(1)$

1. Hash + 双向链表
2. 哨兵节点来简化判断

```cpp

struct ListNode {
    int val;
    ListNode* next;
    ListNode* pre;
}

unsorted_map<int, ListNode*> hash;

```
