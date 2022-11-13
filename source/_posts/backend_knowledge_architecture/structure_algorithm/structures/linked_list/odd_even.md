---
title: 链表系列-奇偶重排
date: 2021-01-30 22:54:03
categories:
- 数据结构与算法
tags: 
- 链表
---

```cpp
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        auto evenHead = new ListNode(-1);
        auto oddHead = new ListNode(-1);

        auto evenTail = evenHead, oddTail = oddHead;

        int k = 1;
        while (head) {
            if (k & 0x1) { //奇
                evenTail->next = head;
                evenTail = head;
            } else {
                oddTail->next = head;
                oddTail = head;
            }
            k++;
            head = head->next;
        }
        
        oddTail->next = NULL; //最后的尾巴需要设置为空
        evenTail->next = oddHead->next;
        return evenHead->next;
    }
};
```