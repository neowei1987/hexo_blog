---
title: 链表反转系列- 每K个一组链表反转
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


每K个反转一次，剩余不到k个，不用反转。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverse(ListNode* head, ListNode* tail) {
        if (head == tail) return head;

        auto x = reverse(head->next, tail);
        head->next->next = head;
        head->next = NULL;
        return tail;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return head;

        auto p = head;
        ListNode* pre = NULL;
        for (int i = 0; i < k; ++i) { 
            //base 不足k个
            if (!p) return head;
            pre = p;
            p = p->next;
        }

        //反转
        reverse(head, pre);

        auto x = reverseKGroup(p, k);
        head->next = x;
        return pre;
    }
};
```
