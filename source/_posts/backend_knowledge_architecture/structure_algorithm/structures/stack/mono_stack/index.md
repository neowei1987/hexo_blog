---
title: 单调栈
date: 2022-02-28 23:34:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 单调栈
- 栈
---

分类
单调递增栈，栈顶元素最大
单调递减栈，栈顶元素最小

一般套路

如果找右边更大的元素，则从前到后构造从底到顶的递减栈;
如果找右边更小的元素，则从前到后构造从底到顶的递增栈;
如果找左边更大的元素，则从后到前构造从底到顶的递减栈;
如果找左边更小的元素，则从后到前构造从底到顶的递增栈;

举一个例子: n个整数的无序数组，找到每个元素后面比它大的第一个数，要求时间复杂度为O(N)。右边比我更大的问题

栈里面存的是啥？
存的是还没有算出来的元素，为啥没有算出来呢，因为还没有遇到比栈顶元素更大的。并且栈顶元素是最小的，所以当前元素也不会大于栈里面的其他元素。

什么时候可以算出来？
后面遇到比栈顶更大的元素，这时候就出栈，并更新数据。

遍历到最后，栈里面还有啥内容？
整个列表中没有比这些元素更大的元素。

```cpp

//单调栈 —— 模板题 AcWing 830. 单调栈
//常见模型：找出每个数左边离它最近的比它大/小的数
int tt = 0;
for (int i = 1; i <= n; i ++ )
{
    while (tt && check(stk[tt], i)) tt -- ;
    stk[ ++ tt] = i;
}

```

---

Given a list of daily temperatures, produce a list that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.

```cpp
vector<int> dailyTemperatures(vector<int>& t) {
    int n = t.size();
    stack<int> s;
    int top = 0;
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && t[i] > t[top = s.top()]){
            t[top] = i - top;
            s.pop();
        }

        s.push(i); //压入了一个更小的，递减栈
    }


    while (!s.empty()) {
        t[s.top()] = 0;
        s.pop();
    }
    return t;
}
```
