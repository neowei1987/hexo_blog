---
title: 动态规划系列-获取不同的翻译方法次数
date: 2021-01-04 11:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags: 
---

## 获取不同的翻译方法次数-题目描述

给定一个数字，我们按照如下规则把它翻译为字符串：

0翻译成”a”，1翻译成”b”，……，11翻译成”l”，……，25翻译成”z”。

一个数字可能有多个翻译。例如12258有5种不同的翻译，它们分别是”bccfi”、”bwfi”、”bczi”、”mcfi”和”mzi”。

请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

样例
输入："12258"

输出：5

## 获取不同的翻译方法次数-总体思路

首先最容易想到的解法是递归，但是我们注意到有很多重复计算，所以更优的做法应该是DP

dp[i]表示0到s[i]这个字符串能够包含的翻译方法。

启发式思考：对于字符串类的DP问题，dp[i]一般是表示以i为结尾的字符串要计算的值。

d[i] = dp[i - 1] + dp[i - 2] when as a ALHPA OR  dp[i - 1] when other

## 获取不同的翻译方法次数-代码实现

```cpp
class Solution {
public:
    string s;
    
    int dfs(int u) {
        int res = 0;
        if (u == s.size()) {
            return 1;
        }
        
        res += (1 * dfs(u + 1)); //长度为1的结果数量
        if (u + 1 < s.size()) {
           int val = 10 * (s[u] - '0') + s[u + 1] - '0';
           if (10 <= val && val <= 25) { 
               res += (1 * dfs(u + 2)); //长度为2的结果数
           }
        }
        
        return res;
    }
    
    int getTranslationCount(string _s) {
        s = _s;
        return dfs(0);
    }
};
```
