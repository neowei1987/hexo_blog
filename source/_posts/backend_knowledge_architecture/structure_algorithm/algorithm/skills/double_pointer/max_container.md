---
title: 一题目多解系列-盛水最多的容器
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

给定一个数组height，长度为n，每个数代表坐标轴中的一个点的高度，height[i]是在第i点的高度，请问，从中选2个高度与x轴组成的容器最多能容纳多少水
1.你不能倾斜容器
2.当n小于2时，视为不能形成容器，请返回0
3.数据保证能容纳最多的水不会超过整形范围，即不会超过2^31-1

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;
        int i = 0, j = height.size() - 1;
        int lmax = 0, rmax = 0;
        while (i < j) {
            lmax = max(lmax, height[i]);
            rmax = max(rmax, height[j]);
            res = max(res, min(lmax, rmax) * (j - i));
            if (lmax < rmax) {
                i++;
            } else {
                j--;
            }
        }

        return res;
    }
};
```
