---
title: 时空复杂度分析
date: 2020-12-28 22:56:03
mathjax: true
categories:
- 算法基础
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

要从暴力、爆搜开始思考，然后再进一步思考怎么去优化复杂度。常见的思考方向如下：
常见的枚举可以看一看枚举的范围是否有序，可以考虑用二分；
双重循环看一看是否可以用双指针；
一些要查找的O(n)复杂度的部分是否可以用map、set;
括号、回文之类可以思考一下能否用栈;
一些暴力搜索的部分看一看是否存在根本不可能到达的状态可以考虑剪枝;
暴力搜索时看看是否有可重复利用的状态用map或数组把状态存起来（记忆化搜索），然后再看看是否可以用动态规划;
一些枚举的范围很大一看就知道不可能ac可能思考一下是否可以直接推出结论或数学公式（贪心的思考方向）;
一些感觉是动态规划的题目貌似，貌似每一个状态都是有规律的可以尝试用打表这种比较赖皮的方法;
一些需要反复计算的部分如果是固定的，可以考虑先计算好然后把它存起来，下次直接拿来用（前缀和思想）;
一些题目的条件和经典题型很像的可以考虑直接套用经典题型（例如01背包模型，完全背包模型）;
一些常见的操作可以看看有没有现成的类或方法可以直接拿来用（例如java大数、排序、字符串反转、拼接等常见操作）;
一些数字的操作可以看看是否涉及到二进制，可以尝试下异或、&这些操作;
动态规划的题目看一看这一次的状态和上一步的状态是否离得很近，如果离得很近可以考虑状态压缩，降低空间复杂度（例如斐波那契，每一次的状态只和前面两步状态有关）;

https://www.educative.io/courses/grokking-dynamic-programming-patterns-for-coding-interviews?aff=K7qB
https://www.educative.io/courses/grokking-the-coding-interview?aff=K7qB


1. Pattern: Cyclic Sort，循环排序
经典题目：
Cyclic Sort (easy)
Find the Missing Number (easy)
Find all Missing Numbers (easy)
Find the Duplicate Number (easy)
Find all Duplicate Numbers (easy)

10. Pattern: Subsets，子集类型，一般都是使用多重DFS
经典题目：
Subsets (easy)
Subsets With Duplicates (easy)
Permutations (medium)
String Permutations by changing case (medium)
Balanced Parentheses (hard)
Unique Generalized Abbreviations (hard)

11. Pattern: Modified Binary Search，改造过的二分
经典题目：
Order-agnostic Binary Search (easy)
Ceiling of a Number (medium)
Next Letter (medium)
Number Range (medium)
Search in a Sorted Infinite Array (medium)
Minimum Difference Element (medium)
Bitonic Array Maximum (easy)

12. Pattern: Top ‘K’ Elements，前K个系列
经典题目：
Top ‘K’ Numbers (easy)
Kth Smallest Number (easy)
‘K’ Closest Points to the Origin (easy)
Connect Ropes (easy)
Top ‘K’ Frequent Numbers (medium)
Frequency Sort (medium)
Kth Largest Number in a Stream (medium)
‘K’ Closest Numbers (medium)
Maximum Distinct Elements (medium)
Sum of Elements (medium)
Rearrange String (hard)

13. Pattern: K-way merge，多路归并
经典题目：
Merge K Sorted Lists (medium)
Kth Smallest Number in M Sorted Lists (Medium)
Kth Smallest Number in a Sorted Matrix (Hard)
Smallest Number Range (Hard)

14. Pattern: 0/1 Knapsack (Dynamic Programming)，0/1背包类型
经典题目：
0/1 Knapsack (medium)
Equal Subset Sum Partition (medium)
Subset Sum (medium)
Minimum Subset Sum Difference (hard)

15. Pattern: Topological Sort (Graph)，拓扑排序类型
经典题目：
Topological Sort (medium)
Tasks Scheduling (medium)
Tasks Scheduling Order (medium)
All Tasks Scheduling Orders (hard)
Alien Dictionary (hard)