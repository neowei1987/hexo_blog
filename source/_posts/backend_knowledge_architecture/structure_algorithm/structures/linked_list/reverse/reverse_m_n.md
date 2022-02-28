---
title: 链表反转系列-m到n链表反转
date: 2021-01-08 23:04:03
updated:
copyright: true
password:
description: 
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表反转
---


逆序第m～n个元素

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
    ListNode* t;

    ListNode* reverseN(ListNode* head, int n) {
        if (!head) return head;
        //base 
        if (n == 1) {
            t = head->next;
            return head;
        }

        //子问题-下一个节点
        auto x = reverseN(head->next, n - 1);
        head->next->next = head;
        head->next = t;
        return x;
    }

    ListNode* reverseBetween(ListNode* head, int m, int n) {
        //base
        if (m == 1) {
            return reverseN(head, n);
        }

        auto x = reverseBetween(head->next, m - 1, n - 1);
        head->next = x;
        return head; //返回的是头
    }
};

```

