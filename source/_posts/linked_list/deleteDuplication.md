---
title: 链表系列-排序链表删除重复节点
date: 2021-01-30 22:54:03
---

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留。

样例1
输入：1->2->3->3->4->4->5

输出：1->2->5
样例2
输入：1->1->1->2->3

输出：2->3

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
    ListNode* deleteDuplication(ListNode* head) {
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto p = dummy;
        while (p->next) {
            auto q = p->next;
            while (q->next && q->next->val == q->val) q = q->next;
            if (p->next == q) p = q;
            else {
                p->next = q->next; 
            }
        }
        
        return dummy->next;
    }
};
```
