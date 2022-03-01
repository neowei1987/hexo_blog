---
title: 链表第一个公共节点
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 链表
- 快慢指针
---

输入两个链表，找出它们的第一个公共结点。

当不存在公共节点时，返回空节点。

样例
给出两个链表如下所示：
A：        a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3

输出第一个公共节点c1

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *findFirstCommonNode(ListNode *h1, ListNode *h2) {
        int c1 = 0, c2 = 0;
       for (auto p = h1; p; p = p->next) c1++;
       for (auto p = h2; p; p = p->next) c2++;
       
       auto p1 = h1;
       auto p2 = h2;
        while (c2 < c1) {
            p1 = h1 = h1->next;
            c2++;
        }
        while (c1 < c2) {
            p2 = h2 = h2->next;
            c1++;
        }

       while (p1 && p2 && p1 != p2) {
           p1 = p1->next;
           p2 = p2->next;
       }

       return p1;
    }
};
```
