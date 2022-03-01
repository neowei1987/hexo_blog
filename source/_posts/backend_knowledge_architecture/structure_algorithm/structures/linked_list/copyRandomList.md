---
title: 链表系列-复制复杂链表
date: 2021-01-04 11:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 链表
---

## 复制复杂链表-题目描述

请实现一个函数可以复制一个复杂链表。

在复杂链表中，每个结点除了有一个指针指向下一个结点外，还有一个额外的指针指向链表中的任意结点或者null。

注意：

函数结束后原链表要与输入时保持一致。

## 复制复杂链表-总体思路

有两种思路：

第一种思路，比较容易想到

（1）遍历一遍，复制出新的node, 并维护好node之间的next关系，同时使用HashMap存储新旧node的映射关系

（2）再遍历一遍，借助hashMap找到新节点对应的random指向过去。

时间复杂度：$O(2n)$, 空间复杂度：$O(n)$

那么我们是否可以不使用额外的空间吗？答案是可以的（此处需要启发式思考，实在想不出我觉得也问题不大！）

（1）遍历一遍，复制新的节点，作为原节点的下一个节点插入到链表中

（2）遍历一遍，如果有random指针，则借助新插入的节点找到新的random指针目标节点

（3）再遍历一遍，访问链表，去掉老的链表节点

时间复杂度：$O(3n)$, 空间复杂度：$O(1)$

## 复制复杂链表-代码实现

```cpp
/**
 * Definition for singly-linked list with a random pointer.
 * struct ListNode {
 *     int val;
 *     ListNode *next, *random;
 *     ListNode(int x) : val(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *copyRandomList(ListNode *head) {
        if (!head) return NULL;
        
        for (auto p = head; p;) {
            auto np = new ListNode(p->val);
            auto next = p->next;
            np->next = next;
            p->next = np;
            p = next;
        }
    
        for (auto p = head; p; p = p->next->next) {
            if (p->random) {
                p->next->random = p->random->next;
            }
        }
        
        auto dummy = new ListNode(-1);
        auto tail = dummy;
        
        for (auto p =head; p;) {
            tail = tail->next = p->next;
            p = p->next = p->next->next;
        }
        
        
        return dummy->next;
    }
};
```