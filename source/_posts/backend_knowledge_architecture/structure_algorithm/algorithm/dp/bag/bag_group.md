---
title: 动态规划背包问题-分组背包
date: 2021-01-11 22:54:03
updated:
copyright: true
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 背包问题
- 动态规划
---
|  分组背包问题  |背包问题系列 |
|  ----  | ----  |
| 问题描述   | 给定N个物品，其中第i组有$C_i$个物品。第i组的第j个物品的体积为$V_{ij}$，价值为$W_{ij}$。有一个容积为M的背包，要求选择一些物品放入背包，使得每组最多选择一个物品并且总体积不超过M的前提下，物品总价值和最大。|
| 状态表示  |F[i,j]表示从前i组选出了总体积为j的物品放入背包，物品的最大价值|
| 转移方程  |$F[i,j]=\begin{cases}F[i-1,j] & \text { 不选第i组的物品} \\ \underset{1 \le k \le C_i}{\mathrm{max}}{F[i - 1,j - V_{ik}] + W_{ik}} &\text{ 选第i个物品} \end{cases}$|
| 阶段划分 | 主阶段：i物品组数是阶段，i与j共同组成状态，k是决策|
| 边界  | F[0,0]=0，其余为负无穷|
| 目标  | $\underset{0 \le j \le M}{\mathrm{max}}{F[N,j]}$|
| 优化  | 正循环做空间优化|
