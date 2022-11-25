---
title: 链表系列-删除重复节点
date: 2022-11-13 22:54:03
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 链表
---

```cpp
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* pre = new ListNode(-100000);
        ListNode* nHead = pre, *tail = pre;
        int preCnt = 2;
        while (head) {
            if (head->val == pre->val) { //如果当前元素 与 前一个元素；
                preCnt++;
            } else {
                if (preCnt == 1) { //如果前面的元素出现一次
                    tail->next = pre;
                    tail = pre;
                    tail->next = NULL;   
                } 
                pre = head;
                preCnt = 1;
            }
            head = head->next;
        }

        if (preCnt == 1) {
            tail->next = pre;
            pre->next = NULL;
        }

        return nHead->next;
    }
};
```
