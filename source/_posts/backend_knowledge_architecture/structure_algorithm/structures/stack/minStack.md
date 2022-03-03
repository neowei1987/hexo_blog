---
title: 栈系列-支持min操作的栈
date: 2021-01-05 00:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 栈
---

## 支持min操作的栈-题目描述

设计一个支持push，pop，top等操作并且可以在O(1)时间内检索出最小元素的堆栈。

push(x)–将元素x插入栈中
pop()–移除栈顶元素
top()–得到栈顶元素
getMin()–得到栈中最小元素
样例
MinStack minStack = new MinStack();
minStack.push(-1);
minStack.push(3);
minStack.push(-4);
minStack.getMin();   --> Returns -4.
minStack.pop();
minStack.top();      --> Returns 3.
minStack.getMin();   --> Returns -1.

## 支持min操作的栈-总体思路

空间换时间，用另外一个stack去储存最小值。

另外，如果要求额外存储空间控制在$O(1)$呢？

思路：

1. 用一个数字来存储当前最小值
2. 栈中存差值（newValueStored = newValue - oldMin、newValueStored = newMin），确保可以根据栈中存的值 与 最小值，能够还原出 原始值。
3. 当发生pop时，能够计算得出新的最小值（oldMin = newValue - newValueStored = NewMin - top）

## 支持min操作的栈-代码实现

```cpp
class MinStack {
public:
    stack<int> ms;
    stack<int> hs;
    
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        ms.push(x);
        if (hs.empty()) hs.push(x);
        else hs.push(min(x, hs.top()));
    }
    
    void pop() {
        ms.pop();
        hs.pop();
    }
    
    int top() {
        return ms.top();
    }
    
    int getMin() {
        return hs.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
```
