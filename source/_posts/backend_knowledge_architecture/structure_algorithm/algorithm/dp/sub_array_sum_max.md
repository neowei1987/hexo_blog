---
title: 动态规划系列-子数组最大和
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 剑指Offer
tags: 
- 动态规划
---

## 子数组最大和--题目描述

输入一个 非空 整型数组，数组里的数可能为正，也可能为负。

数组中一个或连续的多个整数组成一个子数组。

求所有子数组的和的最大值。

要求时间复杂度为O(n)。

样例
输入：[1, -2, 3, 10, -4, 7, 2, -5]

输出：18

## 子数组最大和--思路

子数组的最大值，这是一个求最值问题，十有八九使用动态规划。【这个是我们的经验-求最值问题，十有八九使用动态规划】

拿到一个问题，我们首先要去思考他的解空间有多大？又或者说，计算机用最笨的方法去枚举的话，最多需要枚举多少次。

所有的子数组和的最大值，我需要枚举start, end, 解空间有$n^2$

接着我们再来回答我们接下来要做什么？ 我们需要去检查这一组解是否是最优解。
如何判断呢？ 这个是一个判定问题。

对这个题目而言，我们的解决步骤如下：
从start到end累加得到一个数，累加的时间复杂度是$O(N)$

最终的时间复杂度是$O(n^3)$

## 子数组最大和--代码

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        /*
        dp[i] = num[i] if dp[i - 1] < 0; 
        dp[i] = dp[i - 1] + num[i]; if dp[i - 1] >= 0
        表示以A[i]结尾的子数组的子数组最大和。
        最终的结果，一定是dp[i]中选择一个最大的。

    
        */
        
        int sum = 0;
        int res = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum < 0) {
                sum = nums[i];
            }
            else {
                sum += nums[i];
            }
            
            res = max(res, sum);
        }
        
        return res;
    }
};
```

Maximum sum such that no two elements are adjacent
Given an array of positive numbers, find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence should be adjacent in the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7 should return 15 (sum of 3, 5 and 7).Answer the question in most efficient way.
Examples :
Input : arr[] = {5, 5, 10, 100, 10, 5}
Output : 110

Input : arr[] = {1, 2, 3}
Output : 4

Input : arr[] = {1, 20, 3}
Output : 20
解答思路：
动态规划 dp[i+1] = max(dp[i], dp[i-1]+a[i+1])
维护两个maxSum, 一个包含cur，另一个不包含