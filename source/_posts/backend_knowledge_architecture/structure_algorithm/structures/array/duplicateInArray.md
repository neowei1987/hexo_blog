---
title: 本地交换系列-数组重复数字
date: 2022-02-28 12:56:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 本地交换
---

给定一个长度为 n 的整数数组 nums，数组中所有的数字都在 0∼n−1 的范围内。

数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。

请找出数组中任意一个重复的数字。

注意：如果某些数字不在 0∼n−1 的范围内，或数组中不包含重复数字，则返回 -1；

样例
给定 nums = [2, 3, 5, 4, 3, 2, 6, 7]。

返回 2 或 3。

```cpp
#include <iostream>
#include <algorithm>

class Solution {
public:
    int duplicateInArray(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) 
            if (nums[i] < 0 || nums[i] > n - 1) return -1;
        
        for (int i = 0; i < n; ++i) {
            while (i != nums[i]) {
                int x = nums[i];
                if (nums[x] == x) return x; //如果坑位已经被占了，说明重复了。
                else swap(nums[x], nums[i]);
            }
        }
        x
        return -1;
    }
};
```