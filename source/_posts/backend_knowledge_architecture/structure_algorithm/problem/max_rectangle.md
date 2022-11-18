---
title: 一题目多解系列-柱状图中最大的矩形
date: 2021-01-05 22:09:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 单调栈
- 一题多解
---

## 柱状图中最大的矩形 - 题目描述

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

## 柱状图中最大的矩形-一从暴力开始

首先，思考一下问题的解空间有多大（也就是说有多少种选择），显然一个开始位置、一个结束位置，所以我们可以得到暴力解法的思路：
（1）双层循环确定开始结束位置，也就是矩阵的长
（2）从开始到结束扫描一遍，找到最小值，也就是矩阵的宽
（3）长乘宽得到面积，与答案比较，并更新答案

## 柱状图中最大的矩形-一暴力扫描代码实现

```cpp
int largestRectangleArea(vector<int>& heights) {
    int n = height.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; j++) {
            int minv = INF;
            for (int k = i; k <= j; ++k) {
                minv = min(minv, height[k]);
            }
            res = max(res, (i - j + 1) * minv);
        }
    }
    return res;
}

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> s(heights.size() + 2);
        vector<int> w(heights.size() + 2);
        int p = 0;

        heights.push_back(0);
        int res = 0;
        for (int i = 0; i < heights.size(); ++i) {
            if (heights[i] > s[p]) {
                s[++p] = heights[i];
                w[p] = 1;
            }
            else {
                int width= 0;
                while (s[p] > heights[i]) {
                    width += w[p];
                    res = max(res, width * s[p]);
                    p--;
                }
                s[++p] = heights[i];
                w[p] = width + 1;
            }
        }
        return res;
    }
};vf

public class Solution {
    public int calculateArea(int[] heights, int start, int end) {
        if (start > end)
            return 0;
        int minindex = start;
        for (int i = start; i <= end; i++)
            if (heights[minindex] > heights[i])
                minindex = i;
        return Math.max(heights[minindex] * (end - start + 1), Math.max(calculateArea(heights, start, minindex - 1), calculateArea(heights, minindex + 1, end)));
    }
    public int largestRectangleArea(int[] heights) {
        return calculateArea(heights, 0, heights.length - 1);
    }
}

int largestRectangleArea(vector<int>& heights) {
    int n = height.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int minv = height[i];
        for (int j = i; j < n; j++) { //确保j从小变大
            int minv = INF;
            //如果i看作一个定值，下面这个循环，其实每次都做了相同的工作，重复扫描[i, j]
            //所以可以做累计处理
            //for (int k = i; k <= j; ++k) {
            //    minv = min(minv, height[k]);
            //}
            minv = min(minv, height[j]);
            res = max(res, (i - j + 1) * minv);
        }
    }
    return res;
}

```

时间复杂度：$O(n^3)$ => $O(n^2)$
空间复杂度：$O(1)$

## 柱状图中最大的矩形-进一步思考

还有一种解法，一种**更有智慧**的解法，不像前面的暴力解法那么粗暴，让我们先考虑下哪些肯定不会成为答案。
如果一个格子往两边延伸，一直延伸到有比它更低的格子为止。
![柱状图中最大的矩形-分治法](http://cdn.b5mang.com/202115224849.png)
如果备选答案覆盖了矩形A，那么备选答案的宽度一定会延伸到绿色矩形这里。

假设有N个像上面的这种备选答案，那么最终答案一定是出自这N个备选答案。

为什么我们这么考虑呢？ 因为这样子考虑的话，有利于我们分解子问题。

## 柱状图中最大的矩形-空间换时间版

```cpp
int dfs(vector<int>& height, int l, int r) {
    int p = find_min(height, l, r);

    int left_lower = 0； //往左查找，直到找到比height[p]更小的元素
    int right_lower = 0；//往右查找，直到找到比height[p]更小的元素

    return max(dfs(l, p - 1), dfs(p + 1, r), height[p] * (right_lower - left_lower);
}

int largestRectangleArea(vector<int>& height) {
  return dfs(height, 0, height.size() - 1);
}
```

递推公式：$T(n) = 2*T(n/2) + O(n)$
时间复杂度：$O(nlgn)$
空间复杂度：$O(1)$


## 单调栈解法

找右边，比我小的（利用递增栈）；找到了，就可以计算候选了。

左边的都比我小，left确定了；

新来的，比我小，right也确定了； 所以面积就确定了！
