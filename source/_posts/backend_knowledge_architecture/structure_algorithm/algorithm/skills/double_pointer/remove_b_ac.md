---
title: 双指针系列-移除AC和B
date: 2022-02-26 21:50:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 双指针
---

有字符串,将所有连续的ac跟单独的b去掉后的字符串：如bbbacccccb->ccc; aacceacdby->edy

时间复杂度O(n) 空间复杂度O(n) --> 时间复杂度O(n) 空间复杂度O(1)

这是本题较好的一种解法，设两个指针cur和loc分别从头开始出发，cur每次移动一格，另一个指针loc保留当前的操作位置，如果cur指向的字符是c且loc指向的是a，则将loc回移一位（ac抵消了），如果遇到其他非b的字符，则将loc处的字符置为cur处的字符（++location），一直进行直到到cur到达字符串尾部，此时取字符串开头到loc指针之间的子串即为本题的解。这种解法妙就妙在loc处的字符是即时更新的，一些边界条件都自动消除了。

参考：
https://www.cnblogs.com/SteelArm/p/12773014.html