---
title: 数组系列-奇偶重排
date: 2021-01-05 15:20:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 数组
- 快速排序
- 剑指Offer
---

## 奇偶重排-题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序。

使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分。

样例
输入：[1,2,3,4,5]

输出: [1,3,5,2,4]

<!-- more -->

## 奇偶重排-总体思路

考察点：快速排序思想，双指针（对碰指针技巧）

## 奇偶重排-代码实现

```cpp
class Solution {
public:
    void reOrderArray(vector<int> &nums) {
         int i = 0; 
         int j = nums.size() - 1;
         while (i < j) {
             while (i < j && (!(nums[j] & 1))) {j--;}
             while (i < j && (nums[i] & 1)) {i++;}
  
             if (i < j) {
                 swap(nums[i], nums[j]);
             }
         }
    }
};

```
