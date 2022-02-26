---
title: 动态规划背包问题-完全背包
date: 2021-01-11 22:54:03
updated:
copyright: true
description: 
mathjax: true
categories:
tags: 
---

|  完全背包问题  |背包问题系列 |
|  ----  | ----  |
| 问题描述   | 给定N个物品，其中第i个物品的体积为$V_i$，价值为$W_i$，并且有无限个。有一个容积为M的背包，要求选择一些物品放入背包，使得物品总体积不超过M的前提下，物品总价值和最大。|
| 状态表示  |F[i,j]表示从前i个物品中选出了总体积为j的物品放入背包，物品的最大价值|
| 阶段划分 | 主阶段：已经处理的物品数，以背包中放入到的物品总体积为附加维度|
| 转移方程  |$F[i,j]=\begin{cases}F[i-1,j] & \text {不选第i个物品} \\ F[i,j-V_i] + W_i & \text{if } j \ge V_i  & \text{ 选第i个物品} \end{cases}$|
| 边界  | F[0,0]=0，其余为负无穷|
| 目标  | $\underset{0 \le j \le M}{\mathrm{max}}{F[N,j]}$|
| 优化  | 正循环做空间优化|
| 其他  | 与01背包的区别]|
