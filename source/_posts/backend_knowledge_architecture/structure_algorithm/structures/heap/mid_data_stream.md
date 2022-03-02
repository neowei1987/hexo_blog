---
title: 数据流中位数
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 堆
- 中位数
---

## 题目描述

如何得到一个数据流中的中位数？

如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。

如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

样例
输入：1, 2, 3, 4

输出：1,1.5,2,2.5

解释：每当数据流读入一个数据，就进行一次判断并输出当前的中位数。

## 思路

算法实现时，一个蛮重要的点在每次都要往某一个某一个堆中添加元素（即使不应该插入，也要先插入另一个，再移动元素过去）。

按照刚才提到的步骤来操作，可以大幅减少过多的分支判断，让你的思路更加清晰。

## 代码

```cpp
class Solution {
public:
    priority_queue<int, vector<int>, less<int>> sh; //大根堆，存最小的一半
    priority_queue<int, vector<int>, greater<int>> bh;//小根对，存最大的一半
    
    void insert(int num){
        //总会向大的一半中新增一个。
        if (bh.empty() || num > bh.top()) {
            bh.push(num);
        }
        else { 
            sh.push(num);
            bh.push(sh.top());
            sh.pop();
        }
        
        //如果已经失调，则进行调整
        if (bh.size() == sh.size() + 2) {
            sh.push(bh.top());
            bh.pop();
        }
    }

    double getMedian(){
        if ((bh.size() + sh.size()) & 1) {
            return bh.top();
        }
        else {
            return (bh.top() + sh.top()) / 2.0;
        }
    }
};
```
