---
title: 基数统计-HyperLogLog
date: 2023-05-18
mathjax: true
categories:
- 基数统计
- 剑指Offer
tags: 
---

https://zhuanlan.zhihu.com/p/77289303

由于比特串每个比特都独立且服从0-1分布，因此从左到右扫描上述某个比特串寻找第一个“1”的过程从统计学角度看是一个伯努利过程，例如，可以等价看作不断投掷一个硬币（每次投掷正反面概率皆为0.5），直到得到一个正面的过程。在一次这样的过程中，投掷一次就得到正面的概率为1/2，投掷两次得到正面的概率是