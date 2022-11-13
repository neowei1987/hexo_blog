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
    ListNode* successor;

    //非递归实现
    ListNode* reverseN(ListNode* head, int n) {
        ListNode* pre = NULL;
        auto cur = head;
        while (cur && n > 0) {
            auto next = cur->next; //记录下一个cur
            cur->next = pre; //核心步骤---操作cur的next指针，让其指向pre；
            pre = cur;  //记录前一个
            cur = next; //给下一个cur赋值
            n--;
        }

        head->next = cur;
        return pre;
    }

    ListNode* reverseN(ListNode* head, int n) {
        if (!head) return head;
        //base 
        if (n == 1) {
            successor = head->next; //这一步特别关键，记录当前元素的后继节点，则外面会使用。
            return head;
        }

        //子问题-下一个节点
        auto x = reverseN(head->next, n - 1);
        //head->next 是递归之前的头，也就是递归之后的尾巴
        (head->next)->next = head;
        head->next = successor;
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
