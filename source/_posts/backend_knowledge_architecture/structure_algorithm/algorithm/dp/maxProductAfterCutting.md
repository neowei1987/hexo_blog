---
title: 动态规划系列-切绳子问题
date: 2022-02-26 19:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 动态规划
---

给你一根长度为 n 绳子，请把绳子剪成 m 段（m、n 都是整数，2≤n≤58 并且 m≥2）。

每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]k[1] … k[m] 可能的最大乘积是多少？

例如当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到最大的乘积18。

样例
输入：8

输出：18

自上而下 + 备忘录解法

```cpp
class Solution {
public:
    vector<int> dp;
    
    int dfs(int n) {
        if (dp[n] > 0) {
            return dp[n];
        }
        
        if (n <= 3) {
            dp[n] = n - 1;
            return n - 1; 
        }
        if (n == 4) {
            dp[n] = 4;
            return dp[n];
        }
         if (n == 5) {
            dp[n] = 6;
            return dp[n];
        }
        int max_score = 0;
        for (int i = 2; i <= n - 2; ++i) {
            //分为两种情况：第一刀减在i处；剩下的那一部分可以有两种选择：不剪，或者继续剪
            max_score = max(max_score, max(i * (n - i), i * dfs(n - i)));
        }
        dp[n] = max_score;
        return dp[n];
    }

    int maxProductAfterCutting(int length) {
        dp = vector<int>(length + 5, 0);
        return dfs(length);
    }
};
```