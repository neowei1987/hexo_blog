---
title: 二分系列-旋转数组找最值
date: 2021-01-03 20:47:03
updated:
copyright: true
password:
keywords: 
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 二分
---

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

输入一个升序的数组的一个旋转，输出旋转数组的最小元素。

例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

数组可能包含重复项。

注意：数组内所含元素非负，若数组大小为0，请返回-1。

样例
输入：nums=[2,2,2,0,1]

输出：0

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return -1;
        int n = nums.size() - 1;
        //特判
        while (nums[0] == nums[n]) {n--;}
        //特判
        if (nums[0] <= nums[n]) {
            return nums[0];
        }
        
        //二分模版
        int l = 0, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[0] > nums[mid]) r = mid;
            else  l = mid + 1;
        }
        
        return nums[r];
    }
};

```
