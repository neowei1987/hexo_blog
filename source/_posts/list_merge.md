---
title: 链表系列-有序链表合并
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
- 归并排序
- 剑指Offer
---

## 有序链表合并-题目描述

输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。

样例
输入：1->3->5 , 2->4->5

输出：1->2->3->4->5->5

<!-- more -->

## 二叉树子结构-总体思路

考察点：链表上的归并排序

## 二叉树子结构-代码实现

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
    ListNode* merge(ListNode* l1, ListNode* l2) {
        auto dummy = new ListNode(-1);
        auto tail = dummy;
        while (l1 && l2){
            if (l1->val <= l2->val) {
                tail = tail->next = new ListNode(l1->val);
                l1 = l1->next;
            }
            else {
                tail = tail->next = new ListNode(l2->val);
                l2 = l2->next;
            }
        }
        
        while (l1) {
            tail = tail->next = new ListNode(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            tail = tail->next = new ListNode(l2->val);
            l2 = l2->next;
        }
        
        return dummy->next;
    }  
};
```
