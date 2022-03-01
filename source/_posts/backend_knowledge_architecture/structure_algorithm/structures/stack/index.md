---
title: stack相关的题目
date: 2021-03-14 23:34:03
mathjax: true
categories:
tags: 
---

```cpp

//栈 —— 模板题 AcWing 828. 模拟栈
// tt表示栈顶
int stk[N], tt = 0;

// 向栈顶插入一个数
stk[ ++ tt] = x;

// 从栈顶弹出一个数
tt -- ;

// 栈顶的值
stk[tt];

// 判断栈是否为空,tt 大于0 表示栈不为空。
if (tt > 0)
{

}

```

## 相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [检查合法Stack的弹出序列](isPopOrder.html)  |模拟题，启发式思考|
| | [最小栈](minStack.html)  |模拟题，启发式思考，空间换时间|
