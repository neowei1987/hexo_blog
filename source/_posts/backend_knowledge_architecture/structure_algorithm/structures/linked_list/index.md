---
title: 链表系列-分类汇总
date: 2021-01-11 22:36:03
updated:
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 链表
---

链表，作为一种最简单的数据组织方式，在平常工作中用处非常广泛。

## 关于链表，你一定要知道的

## 链表的常见技巧

1. 链表中的哨兵节点
2. 快慢指针
3. 基于递归的反转问题

```cpp
//单链表 —— 模板题 AcWing 826. 单链表
// head存储链表头，e[]存储节点的值，ne[]存储节点的next指针，idx表示当前用到了哪个节点
int head, e[N], ne[N], idx;

// 初始化
void init()
{
    head = -1;
    idx = 0;
}

// 在链表头插入一个数a
void insert(int a)
{
    e[idx] = a, ne[idx] = head, head = idx ++ ;
}

// 将头结点删除，需要保证头结点存在
void remove()
{
    head = ne[head];
}

//双链表 —— 模板题 AcWing 827. 双链表
// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
int e[N], l[N], r[N], idx;

// 初始化
void init()
{
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}

// 在节点a的右边插入一个数x
void insert(int a, int x)
{
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}

// 删除节点a
void remove(int a)
{
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
```

## 链表相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [删除节点](delete_node.html)  |原地操作，该题并无普遍性|
| | [复杂链表的复制](./copyRandomList.html)  |启发式思考，该题并无普遍性|
| | [链表归并](../list_merge.html)  |归并排序|
