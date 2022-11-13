---
title: 单调队列系列-滑动窗口的最大值
date: 2020-12-27 22:53:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 滑动窗口
- 单调队列
- 队列
---

## 题目描述

给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。

例如，如果输入数组[2, 3, 4, 2, 6, 2, 5, 1]及滑动窗口的大小3,那么一共存在6个滑动窗口，它们的最大值分别为[4, 4, 6, 6, 6, 5]。

注意：

数据保证k大于0，且k小于等于数组长度。
样例
输入：[2, 3, 4, 2, 6, 2, 5, 1] , k=3

输出: [4, 4, 6, 6, 6, 5]

## 思路

1. 借助单调队列
2. 从队头到队尾，元素依次变小，所以称之为单调队列。
3. 队列中存放数组元素下标

## 代码
```cpp
class Solution {
  public:
    vector<int> maxInWindows(vector<int>& nums, int k) {
        deque<int> dq; //双端队列
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            while (dq.size() && dq.back() - dq.front() >= k - 1) dq.pop_front();
            while (dq.size() && nums[i] >= nums[dq.back()]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }

        return res;
    }
};
```