---
title: 贪心算法
date: 2021-03-14 22:58:03
mathjax: true
categories:
tags: 
---

贪心算法 huffman编码

trigger: 针对一组数组，我么定义了限制值、期望值；希望从找找出几个数据，在满足限制的条件下，期望值最大

选择策略：每次选择当前当前情况下，在对限制值同等贡献的情况下，对期望值贡献最大的数据。

分糖果问题、钱币找零、区间覆盖问题

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
|股票买卖系列| [仅买卖一次](../stock_1time.html)  |贪心算法、股票买卖、定序、新的变量与最值|

贪心

a==b 等价于：  a>=b, b <= a


贪心：一般作为正解中的一个步骤出现，用于去掉某些限制条件。
可以小范围搜索+多重限制贪心乱搞，说不定就骗到了100pts呢，考试的时候要勇于乱搞，敢于乱搞
一般一个错误的贪心，都能提炼出一些在某些限制条件下的正确性质。
出题人是傻的，数据是水的，贪心+暴力是能过的，是能$Au$的。

4. Pattern: Merge Intervals，区间合并类型
经典题目：
Merge Intervals (medium)
Insert Interval (medium)
Intervals Intersection (medium)
Conflicting Appointments (medium)