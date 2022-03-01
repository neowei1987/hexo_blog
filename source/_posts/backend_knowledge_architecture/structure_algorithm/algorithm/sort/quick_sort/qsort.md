---
title: 快速排序
categories:
- 数据结构与算法
tags: 
- 排序
- 快速排序
---

两个考察点：分治、双指针实现快速partition

```cpp
//快速排序算法模板
void quick_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        do i ++ ; while (q[i] < x);
        do j -- ; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}

```
