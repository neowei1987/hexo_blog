---
title: 链表系列-链表逆序打印到数组
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
---

输入一个链表的头结点，按照 从尾到头 的顺序返回节点的值。

返回的结果用数组存储。

样例
输入：[2, 3, 5]
返回：[5, 3, 2]

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
    vector<int> printListReversingly(ListNode* head) {
        vector<int> r;
        while (head) {
            r.push_back(head->val);
            head = head->next;
        }
        return vector<int>(r.rbegin(), r.rend()); 
    }
};

```

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
    vector<int> res;

    void reverse(ListNode* head) {
        if (!head) return;
        reverse(head->next);
        res.push_back(head->val);
    }

    vector<int> reversePrint(ListNode* head) {
        reverse(head);
        return res;
    }
};
```
