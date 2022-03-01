---
title: 选择问题-最少次数求最大与最小值
date: 2021-1-2 15:47:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 线性选择
---

Maximum and minimum of an array using minimum number of comparisons
Write a C function to return minimum and maximum in an array. You program should make minimum number of comparisons.

解答思路：

法1: Pair Compare
目标：尽可能的减少比较，如何确定a[i]是不是最小值或者最大值呢？

基于比较，消除不确定性
a[i]跟a[i+1] 比较之后？
a[i] 如果比 a[i+1] 则a[i]才有可能跟max比较；a[i+1] 才有可能跟min比较；

结论：3次比较消除了2个元素的的不确定性；

a[i]跟min, max比较；
a[i+1]跟min, max比较；
结论：4次比较，完成了2个元素的确定性；

法2: Divide and Conquer
如果有两个元素？ 怎么选择最大值最小值？
如果有一个元素，怎么选择最大值最小值？
左半部分已经有了最大值，最小值；右半部分已经有了最小值最大值： 如何确定merge之后的最小值最大值？