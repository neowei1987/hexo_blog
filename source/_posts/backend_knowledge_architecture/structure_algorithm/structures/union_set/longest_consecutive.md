---
title:  并查集系列之最长连续序列
date: 2022-03-01 16:13:03
mathjax: true
categories:
tags: 
---

Longest Consecutive Sequence 求最长连续序列, $O(n)$复杂度

解题思路：

  1. hash来记录是否使用过，以某个元素为中心，向两侧扩展
  2. 带size的并查集