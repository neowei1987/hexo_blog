---
title: 获取丢失的数字
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags: 
---

## 题目描述

一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0到n-1之内。

在范围0到n-1的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

样例
输入：[0,1,2,4]

输出：3

## 实现思路

根据题目描述容易得到：如果把miss的数字补齐，那么我们可以得到序列：$1,2,3,...n$

递增，数组，容易想到是否可以用二分查找。

## 代码实现

```cpp
class Solution {
public:
   int getMissingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (auto x: nums) {
            sum += x;
        }  
        return (n * (n + 1) >> 1) - sum;
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int j = nums.size();
        int i = 0;
        while (i < j) {
            int  m = (i + j) >> 1;
            if (m < nums.size() && nums[m] == m) { //如果是合法的，说明需要往后find.
                i = m + 1;
            } else {
                j = m;
            }
        }
        
        return i;
    }
};

```