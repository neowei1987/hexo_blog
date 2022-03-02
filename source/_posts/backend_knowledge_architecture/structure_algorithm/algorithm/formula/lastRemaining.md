---
title: 圆圈中最后剩下的数字
date: 2020-12-27 23:42:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 递归
---

## 题目描述

0, 1, …, n-1这n个数字(n>0)排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数字。

求出这个圆圈里剩下的最后一个数字。

样例
输入：n=5 , m=3

输出：3

## 思路

1. 递归

## 代码

```cpp
class Solution {
public:
    int lastRemaining(int n, int m){
        if (n == 1) return 0;
        return (lastRemaining(n - 1, m) + m) % n;
    }
};
```
