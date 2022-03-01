---
title: 扑克牌的顺子
date: 2020-12-27 23:34:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 排序
---

## 题目描述

从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。

2～10为数字本身，A为1，J为11，Q为12，K为13，大小王可以看做任意数字。

为了方便，大小王均以0来表示，并且假设这副牌中大小王均有两张。

样例1
输入：[8,9,10,11,12]

输出：true
样例2
输入：[0,8,9,11,12]

输出：true

## 思路

1. 排序，移除0，确保相邻元素不相同

## 代码

```cpp
class Solution {
public:
    bool isContinuous( vector<int> nums ) {
        if (nums.empty()) return false;
        sort(nums.begin(), nums.end());
        int k = 0;
        while (!nums[k]) k++;
        
        for (int i = k + 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1])
                return false;
        }
        
        return nums.back() - nums[k] <= 4;
    }
};
```
