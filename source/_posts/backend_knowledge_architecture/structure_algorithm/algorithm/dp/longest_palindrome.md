---
title: 动态规划系列-最长回文子序列
date: 2022-10-28 11:34:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 动态规划
---

设dp[i][j]为从i到j的字符串，回文子序列的最大长度

IF d[i] == d[j];
    dp[i][j] = dp[i + 1][j - 1] + 2 
ELSE 
    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])

如何遍历，通过图示法可以得知，首先沿着对角线，然后斜向上。

!(图示)[https://pic3.zhimg.com/80/v2-1988e6664d09383c479fc879dcc419fa_1440w.webp]   