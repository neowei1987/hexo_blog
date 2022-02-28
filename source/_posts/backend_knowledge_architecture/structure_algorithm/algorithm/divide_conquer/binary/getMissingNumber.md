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

相关题目

### 寻找重复

给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

1.不能更改原数组（假设数组是只读的）。
2.只能使用额外的 O(1) 的空间。
3.时间复杂度小于 O(n2) 。
4.数组中只有一个重复的数字，但它可能不止重复出现一次

思路：

该题目约束比较多，不能更改原数组，意味着不可以使用数组自hash或者原地交换；

限制了空间，意味着不可以使用某些排序算法或者使用hash map。

可以选择的时间复杂度: $O(n)$、$O(n * lgn)$

可以考虑二分，二分的话有两种：二分数组、二分答案

显然我们的数组并没有排序，所以更有可以是二分答案。

```cpp
class Solution
public: 
    int findDuplicate(vectorzint>&nums){
    int n=nums.size();
    int l=1,r=n-1,ans=-1;
    while(l<=r)
    {
            int mid=(l+r)/2;int cnt=0;
            for(int i=0;i<n;i++){
                cnt=cnt+(nums [i]<=mid)
            }
            if(cnt<=mid)
                l=mid+1;
            else {
                r=mid-1;
                ans=mid
            }
    }
    return ans
}
```