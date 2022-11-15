---
title: 股票买卖系列-无限买卖
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
keywords: [股票买卖,贪心算法]
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 贪心
---

## 题目描述

假设你有一个数组prices，长度为n，其中prices[i]是某只股票在第i天的价格，请根据这个价格数组，返回买卖股票能获得的最大收益
1. 你可以多次买卖该只股票，但是再次购买前必须卖出之前的股票
2. 如果不能获取收益，请返回0
3. 假设买入卖出均无手续费

## 思路

我是上帝，要想利润最大，就是吃到所有的波段！低买高卖！

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        if (prices.empty()) {
            return res;
        }
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                res += prices[i] - prices[i - 1];
            } 
        }

        return res;
    }
};
```