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

扩展问题：

移除重复节点，无排序版本

编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

解答思路：

1. 借助hash来记录val之前是否出现过

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
    ListNode* removeDuplicateNodes(ListNode* head) {
        //hash + 链表
        unordered_map<int, bool> map;

        auto dummy = new ListNode(-1);
        dummy->next = head;

        auto p = head, pre = dummy;
        while (p) {
            if (map[p->val]) { //出现过
                pre->next = p->next;
            }
            else {
                pre = p;
            }
            map[p->val] = true;
            p = p->next;
        }

        return dummy->next;
    }
};
```
