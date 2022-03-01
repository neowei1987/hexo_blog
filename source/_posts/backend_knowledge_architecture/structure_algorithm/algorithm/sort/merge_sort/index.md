---
title: 归并排序
categories:
- 经典题目
- 数据结构与算法
tags: 
- 排序
- 归并排序
---

```cpp
//归并排序算法模板
void merge_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int mid = l + r >>1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    vector<int> tmp(r -l + 1);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r ) {
        if (q[i] < q[j]) tmp[k++] = q[i++];
        else  tmp[k++] = q[j++];
    }

    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    for (i = l, k = 0; i <= r; i++, k++) q[i] = tmp[j];
}
```
