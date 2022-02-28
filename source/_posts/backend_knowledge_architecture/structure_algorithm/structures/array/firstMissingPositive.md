---
title: 本地交换系列-缺失的第一个正数
date: 2021-01-10 10:47:03
updated:
copyright: true
password:
keywords: []
description:
mathjax: true
categories:
- [数据结构与算法]
tags:
- 本地交换
---

## 缺失的第一个正数 - 题目描述

给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

## 缺失的第一个正数 - 总体思路

本地交换法不太容易想到，所以该题目定级为困难。题目让我们找缺失的第一个正数？

我们不妨做一下**逆向思考**，假设一个正数都不缺失呢？我们会得到什么？ 一般情况下，我们的元素下标与元素的值会一一对应，从1到N。

所以，我们考虑尝试着把一个元素i都找到他对应的位置i上，如果位置i被占了，我也强制把位置i的元素移走，重复整个过程。

## 缺失的第一个正数 - 代码实现

```cpp

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        //1~N
        //一定可以为i找到一个合适的坑；
       for (int i = 1; i <= n; ++i) {
           int x = nums[i - 1];
            while (x >= 1 && x <= n && x != nums[x - 1]) {
                swap(nums[x - 1], nums[i - 1]);
                x = nums[i - 1];
            }
       }

       for (int i = 1; i <= n; ++i) {
           if (nums[i - 1] != i) {
               return i;
           }
       }

       return n + 1;
    }
};
```
