---
title: 单调队列
date: 2022-02-28 21:53:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 单调队列
- 队列
---

```cpp
//单调队列 —— 模板题 AcWing 154. 滑动窗口
//常见模型：找出滑动窗口中的最大值/最小值
int hh = 0, tt = -1;
for (int i = 0; i < n; i ++ )
{
    while (hh <= tt && check_out(q[hh])) hh ++ ;  // 判断队头是否滑出窗口
    while (hh <= tt && check(q[tt], i)) tt -- ;
    //新的元素入队
    q[ ++ tt] = i;
}
```
