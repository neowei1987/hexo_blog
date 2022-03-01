---
title: 时空复杂度分析
date: 2020-12-28 22:56:03
mathjax: true
categories:
tags: 
---

一般ACM或者笔试题的时间限制是1秒或2秒。

在这种情况下，C++代码中的操作次数控制在 $10^7$ 为最佳。

下面给出在不同数据范围下，代码的时间复杂度和算法该如何选择：

n≤30 => 指数级别, dfs+剪枝，状态压缩dp

n≤100 => $O(n^3)$，floyd，dp，高斯消元

n≤1000 => $O(n^2),O(n^2logn)$，dp，二分，朴素版Dijkstra、朴素版Prim、Bellman-Ford

n≤10000 => $O(n*\sqrt{n})$，块状链表、分块、莫队

n≤100000  => $O(nlogn)$ => 各种sort，线段树、树状数组、set/map、heap、拓扑排序、dijkstra+heap、prim+heap、spfa、求凸包、求半平面交、二分、CDQ分治、整体二分

n≤1000000  => $O(n)$, 以及常数较小的 $O(nlogn)$ 算法 => 单调队列、 hash、双指针扫描、并查集，kmp、AC自动机，常数比较小的 $O(nlogn)$ 的做法：sort、树状数组、heap、dijkstra、spfa

n≤10000000 => $O(n)$，  双指针扫描、kmp、AC自动机、线性筛素数

n≤$10^9$ => $O(\sqrt{n})$， 判断质数

n≤$10^{18}$ => $O(logn)$，  最大公约数，快速幂

n≤$10^{1000}$ => $O((logn)^2)$，    高精度加减乘除

n≤$10^{100000}$  => $O(logk×loglogk)$，k表示位数，  高精度加减、FFT/NTT
