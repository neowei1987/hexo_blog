---
title: 找到仅出现一次的数
date: 2021-01-03 23:16:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags: 
---

## 找到仅出现一次的数，其他数出现二次

一个整型数组里除了两个数字之外，其他的数字都出现了两次。

请写程序找出这两个只出现一次的数字。

你可以假设这两个数字一定存在。

样例
输入：[1,2,3,3,4,4]

输出：[1,2]

## 实现思路-基于XOR

## 代码实现-基于XOR

```cpp
class Solution {
public:
        vector<int> findNumsAppearOnce(vector<int>& nums) {
        int s = 0;
        for (auto x: nums) {
            s ^= x;
        }

        int u = s & -s;
        vector<int> g0, g1;

        for (auto x: nums) {
            if (x & u ) g1.push_back(x);
            else g0.push_back(x); 
        }

        vector<int> res(2, 0);
        for (auto x : g0) {
            res[0] ^= x;
        }
        for (auto x : g1) {
            res[1] ^= x;
        }

        return res;
    }
};
```

## 找到仅出现一次的数，其他数都出现三次

在一个数组中除了一个数字只出现一次之外，其他数字都出现了三次。

请找出那个只出现一次的数字。

你可以假设满足条件的数字一定存在。

思考题：

如果要求只使用 O(n) 的时间和额外 O(1) 的空间，该怎么做呢？
样例
输入：[1,1,1,2,2,2,3,4,4,4]

输出：3

## 实现思路-基于Bit位

## 代码实现-基于Bit位

```cpp
class Solution {
public:
    int findNumberAppearingOnce(vector<int>& nums) {
        vector<int> bitmap(32, 0);
        for (auto x: nums) {
            for (int i = 0; i < 32; ++i) {
                if (x & (1 << i)) bitmap[i]++;
            }
        }
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            if (bitmap[i] % 3) {
                res += 1 << i;
            }
        }
        return res;
    }
};

```
