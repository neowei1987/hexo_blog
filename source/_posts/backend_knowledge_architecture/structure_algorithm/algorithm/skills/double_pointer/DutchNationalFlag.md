---
title: 双指针系列-荷兰旗问题
date: 2022-2-26 22:00:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 双指针
- 快速排序
---

0,1,2

分为三段：0段、未判定段、2段，用三个指针（s0, cur, s2)指向每一段的当前位置。

s0并不是指向0段的最后一个元素，而是指向最后一个元素的下一个元素。s2类似。

如果A[cur]=0，则s0（其实指向1）,cur互换位置； s0++; cur++;
如果A[cur]=1，则cur++;
如果A[cur]=2,则s2，cur互换位置； s2--; cur不变；
