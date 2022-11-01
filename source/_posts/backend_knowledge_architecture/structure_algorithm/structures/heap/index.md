---
title: 堆
date: 2022-02-28 21:20:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 堆
---

二叉堆，包括最大堆、最小堆

最大特点：在$O(1)$时间内找到最小（最大）元素

堆的常见应用：

1. 堆排序
2. 用两个堆（一个最大堆，一个最小堆）来维护/查询第K大/小的操作
3. 贪心算法优化

```cpp
堆 —— 模板题 AcWing 838. 堆排序, AcWing 839. 模拟堆
// h[N]存储堆中的值, h[1]是堆顶，x的左儿子是2x, 右儿子是2x + 1
// ph[k]存储第k个插入的点在堆中的位置
// hp[k]存储堆中下标是k的点是第几个插入的
int h[N], ph[N], hp[N], size;

// 交换两个点，及其映射关系
void heap_swap(int a, int b)
{
    swap(ph[hp[a]],ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int u)
{
    int t = u;
    if (u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= size && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t)
    {
        heap_swap(u, t);
        down(t);
    }
}

void up(int u)
{
    while (u / 2 && h[u] < h[u / 2])
    {
        heap_swap(u, u / 2);
        u >>= 1;
    }
}

// O(n)建堆
for (int i = n / 2; i; i -- ) down(i);
```

