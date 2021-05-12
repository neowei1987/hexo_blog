---
title: 链表系列-链表倒数第K个节点
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
- 双指针
- 剑指Offer
---

## 链表倒数第K个节点-题目描述

输入一个链表，输出该链表中倒数第k个结点。

注意：

k >= 0;
如果k大于链表长度，则返回 NULL;
样例
输入：链表：1->2->3->4->5 ，k=2

输出：4

<!-- more -->

## 链表倒数第K个节点-总体思路

考察点：双指针（一前一后的快慢指针）

## 链表倒数第K个节点-代码实现

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
    ListNode* findKthToTail(ListNode* head, int k) {
        auto fast = head;
        auto slow = head;
        while (fast && k) {
            k--;
            fast = fast->next;
        }
        
        if (k > 0) return NULL;
        if (slow == fast) return NULL;
        
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        
        return slow;
    }
};
```
