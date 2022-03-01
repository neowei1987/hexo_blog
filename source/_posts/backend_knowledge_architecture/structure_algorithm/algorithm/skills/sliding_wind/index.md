---
title: 滑动窗口系列-概览
date: 2021-01-05 15:44:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 滑动窗口
- 剑指Offer
---

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [最长无重复字串](../longestSubstringWithoutDuplication.html)  |滑动窗口、字符串类|

```cpp
//滑动窗口 模版
for (int i = 0, j = 0; i < n; i ++ )
{
    //i是新进入窗口的元素
    while (j < i && check(i, j)) j ++ ; //j是可能要滑出窗口的元素

    // 具体问题的逻辑
}
```
