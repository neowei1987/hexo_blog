---
title: 位运算系列-比特位计数
date: 2021-01-10 20:42:03
updated:
copyright: true
description: 
mathjax: true
categories:
tags: 
---

## 比特位计数 - 题目描述

给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

## 比特位计数 - 代码实现

```cpp
class Solution {
public:
    /*
    int lowbit(int n) {
        return n & (~n);
    }
    */
    vector<int> countBits(int num) {
        vector<int> dp(num + 1);
        for (int i = 1; i <= num; ++i) {
            dp[i] = dp[i & i - 1] + 1; //每次n&n-1会抹掉最后一个1
        }

        return dp;
    }
};
```