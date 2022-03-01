---
title: 二进制表示中1的个数
date: 2021-02-024 21:16:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 位运算
---

输入一个32位整数，输出该数二进制表示中1的个数。

注意：

负数在计算机中用其绝对值的补码来表示。
样例1
输入：9
输出：2
解释：9的二进制表示是1001，一共有2个1。
样例2
输入：-2
输出：31
解释：-2在计算机里会被表示成11111111111111111111111111111110，
一共有31个1。

```cpp
class Solution {
public:
    int NumberOf1(int n) {
        int c = 0;
        while (n) {
            n = n & (n - 1);
            c++;
        }
        return c;
    }
};
```
