---
title: 动态规划系列-矩阵中找一条最长的递增路径
date: 2022-02-26 19:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 动态规划
---

求解一个矩阵中找一条最长的递增路径？

可能解法：有向图DFS和记忆化搜索处理

dp[i][j]表示以(i,j)出发的最长路径。

该题目用常规的DP很难完成，因为他没有base condition，不知道从何处开始计算。
