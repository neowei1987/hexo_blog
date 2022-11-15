---
title: 一题目多解系列-接雨水问题
date: 2021-01-05 18:56:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 双指针
- 一题多解
---

## 接雨水问题 - 题目描述

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。

示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6

## 接雨水问题-一开始的思路

经典解法包括：
（1）单调栈，左右遇到的最大值
（2）双指针

首先，也是最重要的，先把题目搞清楚（好多时候解不出题是由于题目没有完全理解、没有理解完全或者完全没有理解）。
按照题意，一个格子能够接的水，取决于该格子向前、向后遇到的最大值，两个最大值取最小值；而我之前曾经按照往前、往后遇到的比该格子高的格子来算了。

其次，让我们考虑最暴力的做法是什么？暴力扫描。

## 接雨水问题-一暴力扫描代码实现

```cpp
int trap(vector<int>& height) {
    int n = height.size();
    int res = 0;
    for (int i = 1; i < n; ++i) {

        //往左找到最大值
        int lmax = 0;
        for (int j = 0; j < i; ++j) {
            lmax = max(lmax, height[j]);
        }

        //往右找到最大值
        int rmax = 0;
        for (int j = i + 1; j < i; ++j) {
            rmax = max(rmax, height[j]);
        }

        res += min(rmax, lmax) - height[i];

    }
}
```

时间复杂度：$O(n^2)$
空间复杂度：$O(1)$

## 接雨水问题-进一步思考

观察上面的代码，有很多重复计算，例如计算i左边的最大值时，扫描范围是[0, i - 1];当计算i+1左边的最大值时，扫描范围是[0, i]，显然是完全包含[0, i - 1]的，
对于重复计算，我们继续采用空间换时间的套路，用数组lmax[i]来存储[0, i - 1]的最大值；这样子存储之后，如果再计算lmax[i + 1]只要拿lmax[i]跟height[i + 1]比较即可。

## 接雨水问题-空间换时间版

```cpp
int trap(vector<int>& height) {
    int n = height.size();
    int res = 0;
    int lmax[N], rmax[N];
    //正序遍历
    for (int i = 1; i < n; ++i) {
        lmax[i] = max(lmax[i - 1], height[i - 1]);
    }

    //倒序遍历 
    for (int i = n; i >= 0; --i) {
        rmax[i] = max(rmax[i + 1], height[i + 1]);
    }

    for (int i = 1; i < n; ++i) {
        res += min(lmax[i], rmax[i]) - height[i];
    }
}
```

时间复杂度：$O(n)$
空间复杂度：$O(n)$

## 接雨水问题-能不能把空间复杂度优化掉？

其实，上面的时间复杂度已经是最优了，有没有可能把空间也优化掉呢？我们注意到lmax[i]仅跟lmin[i-1]有关系，这个对于我们做空间压缩是很好的；
剩下的就是，我们能不能把lmax,rmax立即用上，而不需要存起来呢？答案是可以的。我们可以把上面的循环写在一起，用i、j两个指针分别指向左右两个端点，在遍历的过程中，直接把前面出的lmax, rmax立即用上。

## 接雨水问题-双指针优化版

```cpp
int trap(vector<int>& height) {
    int n = height.size();
    int res = 0;
    int lmax, rmax;
    int i = 1, j = n - 2;

    while (i < j) {
        lmax = max(lmax, height[i - 1]);
        rmax = max(rmax, height[j + 1]);
        if (lmax < rmax) {
            res += lmax - height[i];
            i++;
        }
        else {
            res += rmax - height[j];
            j--;
        }
    }
    return res;
}
```

```cpp

class Solution {
public:
    int trap(vector<int>& height) {
        int lmax = 0, rmax = 0;
        int l = 0, r = height.size() - 1;
        int sum = 0;

        while (l <= r) {
            for (; l <= r && (lmax = max(height[l], lmax)) <= rmax; ++l) {
                sum += lmax - height[l];
            }
            for (; r >= l && (rmax = max(height[r], rmax)) <= lmax; r--) {
                sum += rmax - height[r];
            }
        } 

        return sum;
    }
};

```

时间复杂度：$O(n)$
空间复杂度：$O(1)$

单调栈解法

```cpp

class Solution {
public:
    /**
     * max water
     * @param arr int整型vector the array
     * @return long长整型
     */
    long long maxWater(vector<int>& arr) {
        stack<int> s;
        s.push(-1);
        int res = 0;
        for (int i = 0; i < arr.size(); ++i) {
            while (s.top() != -1 && arr[s.top()] < arr[i]) {
                int cur = s.top(); //当前计算的格子
                s.pop();
                int left = s.top();
                if (left >= 0) {
                    res += (min(arr[left], arr[i]) - arr[cur]) * (i - left - 1);
                    //cout << "i:" << i << ", cur:"  << cur << ", res: " << res << endl;
                }
            }

            s.push(i);
        }

        return res;
    }
};

```