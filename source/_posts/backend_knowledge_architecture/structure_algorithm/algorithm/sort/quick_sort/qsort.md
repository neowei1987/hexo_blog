---
title: 快速排序
categories:
- 数据结构与算法
tags: 
- 排序
- 快速排序
---

两个考察点：分治、双指针实现快速partition

时间复杂度：

平均 lgn;
最坏：n^2
最好：

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
            q[i] = q[j];
            while (i < j && q[i] < x) i++;  //注意<=，而不能是<
            q[j] = q[i]
        }  
        a[i] = x;

        //qselect(q, l, j, k);
        //qselect(q, j + 1, r, k);
        
        if (i - l + 1 == k ) return;
        else if (i - l + 1 < k) qselect(q, j + 1, r, k - (i - l + 1)); 
        else  qselect(q, l, j - 1, k);
    }
};
```

对于有序数组，上面把start作为Pivot的方法，会让算法时间复杂度退化为O(N^2),导致超时。
对数组进行shuffle，能解决有序数组的问题，但是无法解决所有元素全部相同的问题。当所有元素都一样时，shuffle无用，时间复杂度还是O(N^2)
于是就有了下面的解法。这种方法，返回了中间区域的左右边界，让问题迅速简化！

```cpp

void quick_sort_3part(int q[], int l, int r) {
    if (l >= r) return;
    
    swap(q[l], q[l + rand() % (r - l + 1)]); //随机化
    int lt = l, gt = r, i = l + 1, x = q[l];
    // 6,4,1,3,6,6,6,6,4,3,10,45,32
    // |     |       |     |
    // l    lt      i     gt
    // 三路快排，确定等于主元pivot的左右边界
    while (i <= gt) {
        if (q[i] < x) swap(q[i++], q[++lt]);  //gt左边的元素都比x大，但是gt指向的不一定大
        else if (q[i] > x) swap(q[i], q[gt--]);//把比x大的元素，换到后面了；但换回来的元素不一定“满足条件”，所以i不能变，需要再比较一次！
        else i++;// 等于主元，则继续
    }
    swap(q[l], q[lt]);

    quick_sort_3part(q, l, lt - 1);
    quick_sort_3part(q, gt + 1, r);
}
```
