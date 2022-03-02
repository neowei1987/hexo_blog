---
title: 桶排序思想经典题目
date: 2020-12-30 12:53:03
mathjax: true
categories:
- 数据结构与算法
- 经典题目
tags: 
- 桶排序
- 排序
---

https://www.jianshu.com/p/45f4c5f74c8e

问题：

最大间隙问题。给定 n 个实数，求这n个实数在数轴上相邻2个数之间的最大差值，设计解最大间隙问题的线性时间算法。

分析：

该问题最先想到可能就是排序后计算，但排序的时间复杂度最少为O(nlongn)，不能满足题意的线性时间算法。

所以有一个解决该问题的算法，筒排序。

该算法的思想为，将n个数的最大值、最小值找到，在[ min ,max ]区间内，分成n-1个等大的区间，每个区间的大小为

len = （max - min）/（n-1），然后将n个数字填入到这n-1个区间中，并根据填入的数，找到该区间内数字的最大值与最小值。除去两边的最大值和最小值，只需要将n-2 个数字填入到 n-1个区间中，根据抽屉原理，那至少有一个空的区间，所以，最大间隙一定产生在两个不同区间之间。

为什么从$O(nlgn)$可以优化到$O(n)$?

对数据进行处理之后，在对处理之后的序列进行相关操作，这是一种很常见的解决问题的思路。

其中，第一步的处理包括：排序、对数据合理的分组等; 借助第一步的预处理，然后再根据一些数学特性去排除一些肯定不可能成为答案的解，从而提到算法效率。

```cpp
const int N = 100010;
struct Bucket {
    bool used;
    int minv;
    int maxv;
} buckets [N];



class Solution {
public:

    int maximumGap(vector<int>& nums) {
        memset(buckets, 0, sizeof(buckets));
        if (nums.size() < 2) return 0;
        //桶排序 + 鸽巢原理
        int minv = 0x3f3f3f3f, maxv = 0, n = nums.size();
        for (auto x : nums) {
            if (x <= minv)  minv = x;
            if (x >= maxv) maxv = x;
        }

        int gap = max(1, (maxv - minv) / (n - 1));
        int gap_cnt = (maxv -minv) / gap + 1;

        for (auto x : nums) {
            int i = (x - minv) / gap;
            cout << i  << " "<< x << " "<< gap<< endl;

            if (!buckets[i].used) {
                buckets[i].used = true;
                buckets[i].minv = 0x3f3f3f3f;
                buckets[i].maxv = 0;
            }
            buckets[i].minv = min(buckets[i].minv, x);
            buckets[i].maxv = max(buckets[i].maxv, x);
        }  

        int res = 0;
        int pre = minv;
        for (int i = 0; i < gap_cnt; ++i) {
            if (!buckets[i].used) continue;
            res = max(buckets[i].minv - pre, res);
            pre = buckets[i].maxv;
        }

        return res;
    }
};
```
