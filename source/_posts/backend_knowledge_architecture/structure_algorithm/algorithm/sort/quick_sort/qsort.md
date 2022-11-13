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

下面这道题目是基于快排思想的TopK，他们的partion逻辑不太一样，其中一个很重要的点在于：
quickselect要求把输入分成了三部分，[<=X] X [>X]；
而上面的quicksort只是把输入分成了两部分，[<X],[>=X]或者[<=X], [>X]
分割点在某一区间内，但是不一定在区间的两端；

```cpp
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        qselect(input, 0, input.size() - 1, k);
        vector<int> res(k);
        for (int i = 0; i < k; ++i) {
            res[i] = input[i];
        }
        return res;
    }

    void qselect(vector<int>& q, int l, int r, int k) {
        if (l >= r) return;
        
        int i = l, j = r, x = q[l];
        while (i < j) {
            while(i < j && q[j] > x) j--; //优先从j开始
            while (i < j && q[i] <= x) i++;  //注意<=，而不能是<
            if (i < j) swap(q[i], q[j]);
        }  
        swap(q[l], q[i]); //i一定是小于等于l的；所以可以换一下！

        //qselect(q, l, j, k);
        //qselect(q, j + 1, r, k);
        
        if (i - l + 1 == k ) return;
        else if (i - l + 1 < k) qselect(q, j + 1, r, k - (i - l + 1)); 
        else  qselect(q, l, j - 1, k);
    }
};
```