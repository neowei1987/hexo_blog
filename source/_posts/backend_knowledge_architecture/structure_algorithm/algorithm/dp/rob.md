---
title: 变种题系列-打家劫舍
date: 2022-03-02 13:09:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 动态规划
- 变种题
---

### 普通版本打家劫舍

普通DP，第i家抢还是不抢？

### 环形版本打家劫舍

思路：

由于首尾也属于相邻，因此需要分别判断，以第一家是否打劫分成两个问题

第一家抢：最后一家一定不能抢，从第0个到len-2做动态规划

第一家不抢：从1到len-1做动态规划

然后比较找出最大值

### 二叉树版本打家劫舍

不太像是一个DP问题，他的本质是一个DFS问题。

本质上所有的DP问题都可以看作DFS + 备忘录。
