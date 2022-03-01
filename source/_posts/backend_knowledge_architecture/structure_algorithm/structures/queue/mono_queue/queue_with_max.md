---
title: 单调队列系列-支持最大值的队列
date: 2021-1-8 00:34:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 单调队列
- 队列
---

## 支持最大值的队列 - 题目描述

请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

1 <= push_back,pop_front,max_value的总操作数 <= 10000

1 <= value <= 10^5

## 支持最大值的队列-实现思路

首先，默写下普通队列的模版：

```cpp
int q[N];
int hh = 0;
int tt = -1;
//push
q[++tt] = x;
//pop
q[hh++];
//is empty
hh > tt;
```

其次，默写下单调队列的模版：

```cpp
    for (int i = 0; i < n; ++i) {
        while (tt >= hh && check_out(q[hh])) hh++; //判断是否滑出窗口
        while (tt >= hh && check(q[tt])) tt--;
        q[++tt] = i;
    }
```

最后为什么会想到单调队列？

一句话：如果一个后入队的元素比我还大，那么我永无出头之日！

## 支持最大值的队列-代码实现

```cpp
 class MaxQueue {
public:
    MaxQueue() {
        memset(q, 0, sizeof(q));
        hh = 0;
        tt = -1;
    }
    
    int max_value() {
        if (dq.size()) return q[dq.front()];
        else return -1;
    }
    
    void push_back(int value) {
        q[++tt] = value;
        //if (dq.size() && value >= q[dq.front()]) dq.clear();
        while (dq.size() && value > q[dq.back()]) dq.pop_back();
        dq.push_back(tt);
    }
    
    int pop_front() {
       if (tt < hh) return -1;

       //当前的hh
       if (dq.size() && dq.front() == hh) {
           dq.pop_front();
       }

       return q[hh++];
    }

private:
    int q[10010];
    int hh; //队头
    int tt; //队尾
    std::deque<int> dq;
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```
