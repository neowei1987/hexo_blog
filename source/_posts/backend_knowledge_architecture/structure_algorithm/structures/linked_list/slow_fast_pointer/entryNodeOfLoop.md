---
title: 链表系列-链表环入口
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- 剑指Offer
- 数据结构与算法
tags: 
- 链表
- 快慢指针
---

## 链表环入口-题目描述

给定一个链表，若其中包含环，则输出环的入口节点。

若其中不包含环，则输出null。

样例
QQ截图20181202023846.png

给定如上所示的链表：
[1, 2, 3, 4, 5, 6]
2
注意，这里的2表示编号是2的节点，节点编号从0开始。所以编号是2的节点就是val等于3的节点。

则输出环的入口节点3.

<!-- more -->

## 链表环入口-总体思路

考察点：双指针（一前一后的快慢指针）

## 链表环入口-代码实现

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
    ListNode *entryNodeOfLoop(ListNode *head) {
        if (!head || !head->next || !head->next->next) return NULL;
        
        auto fast = head, slow = head;
        while (fast && fast->next && slow) {
            slow = slow->next; /慢的走一步
            fast = fast->next->next;  //快的走两步
            if (slow == fast) {
                break;
            }
        }
        
        if (fast != slow || !fast || !fast->next || !slow) {
            return NULL;
        }
        
        //再重新走一遍
        slow = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        
        return fast;
    }
};
```
