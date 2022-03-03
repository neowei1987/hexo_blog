---
title: 动态规划系列-不相邻序列最大和
date: 2022-02-26 20:34:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 动态规划
---

Maximum sum such that no two elements are adjacent
Given an array of positive numbers, find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence should be adjacent in the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7 should return 15 (sum of 3, 5 and 7).Answer the question in most efficient way.
Examples :
Input : arr[] = {5, 5, 10, 100, 10, 5}
Output : 110

Input : arr[] = {1, 2, 3}
Output : 4

Input : arr[] = {1, 20, 3}
Output : 20

## 不相邻序列最大和--思路

遍历array 中的所有元素，设置两个变量：

excl[i]: 不包含i元素的最大和

incl[i]: 包含i元素的最大和

更新当前元素的 excl 和 incl：

不包含当前元素的最大和 excl[i] = max(incl[i-1]， excl[i-1])

包含当前元素的最大和 incl = excl[i-1]+A[i] (元素不能相邻)

因为只与前一项有关，所以可以用空间压缩。
