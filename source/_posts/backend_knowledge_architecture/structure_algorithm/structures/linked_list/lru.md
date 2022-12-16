---
title: 链表系列-LRU缓存
date: 2022-02-28 21:40:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 链表
- 哈希
---

什么是LRU缓存，怎么设计的LRU缓存。
时间复杂度：$O(1)$

1. Hash + 双向链表
2. 哨兵节点来简化判断

```cpp

struct ListNode {
    int val;
    ListNode* next;
    ListNode* pre;
}


class LRUCache {
private:
    unordered_map<int, ListNode*> hash;
    ListNode* head;
    ListNode* tail;
    int n;

    LRUCache(int nn) {
        n = nn;
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->pre = head;
    } 

    void put(int k, int v) {
        ListNode* r = get2(k);
        if (r != NULL) return;

        ListNode* node = NULL;
        if (hash.size() > n) {
            //链表上移除
            auto node = tail->pre;
            node->next->pre = node->pre;
            node->pre->next = node->next;  
            //hash移除 
            hash.erase(node->k);
        }
        else {
            node = new ListNode();
        }

        node.val = v;
        //将node放在头部
        node->next = head->next;
        node->pre = head;
   
        head->next->pre = node;
        head->next = node;

        hash[k] = node;

    }

    ListNode* get2(int k) {
        auto it = hash.find(k);
        if it == hash.end() {
            return NULL;
        }

        auto node = *it;
        
        //移除
        node->next->pre = node;
        node->pre->next = node->next;

        node->next = head->next;
        node->pre = head;
   
        head->next->pre = node;
        head->next = node;
    }

    int get(int k) {
        ListNode* r = get2(k);
        if (r == NULL) return -1;
        else r->val;
    }
};

```
