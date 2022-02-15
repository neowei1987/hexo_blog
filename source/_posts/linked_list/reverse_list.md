---
title: 链表反转系列-三道链表反转题
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

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return NULL;
        //base
         if (!head->next) return head;

        //对子问题进行递归-当前节点的下一个
        auto nh = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return nh;
    }
};
```

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