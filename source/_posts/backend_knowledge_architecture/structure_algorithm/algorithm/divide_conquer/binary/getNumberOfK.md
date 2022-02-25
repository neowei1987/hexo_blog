---
title: 二分系列-数字在排序数组中出现的次数
date: 2021-01-03 20:47:03
updated:
copyright: true
password:
keywords: 
description: 
mathjax: true
categories:
tags: 
---

统计一个数字在排序数组中出现的次数。
例如输入排序数组[1, 2, 3, 3, 3, 3, 4, 5]和数字3，由于3在这个数组中出现了4次，因此输出4。

样例
输入：[1, 2, 3, 3, 3, 3, 4, 5] ,  3

输出：4

```cpp
class Solution {
public:
    int getNumberOfK(vector<int>& nums , int k) {
    if (nums.empty())  return 0;
    int l = 0, r = nums.size() - 1;
    // 左边界
    while (l < r) {
        int mid = l + r >> 1;
        if (nums[mid] < k) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    if (nums[r] != k) return 0;
    int left = r;

    // 右边界
    l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r  + 1 >> 1;
        if (nums[mid] > k) {
            r = mid - 1;
        }
        else {
            l = mid;
        }
    }

    return r - left + 1;
}
};
```
