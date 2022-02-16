---
title: 链表系列-链表反转
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
- 剑指Offer
---

## 链表反转-题目描述

定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。

思考题：

请同时实现迭代版本和递归版本。
样例
输入:1->2->3->4->5->NULL

输出:5->4->3->2->1->NULL

<!-- more -->

## 链表反转-总体思路

## 链表反转-非递归版代码实现

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

    ListNode* reverseList(ListNode* head) {
       if (!head) return head;
       
       ListNode* pre = NULL;
       while (head) {
           auto t = head->next;
           head->next = pre;
           pre = head;
           head = t;
       }
       
       return pre;
    }
};

```

## 链表反转-递归版代码实现

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

    ListNode* reverseList(ListNode* head) {
        _reverseList(head);
    }

    ListNode* _reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        auto t = head->hext;
        _reverseList(t)
        t->next = head;
    }
};
```
