---
title: 栈系列-检查合法Stack的弹出序列
date: 2021-01-04 11:42:03
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

## 检查合法Stack的弹出序列-题目描述

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。

假设压入栈的所有数字均不相等。

例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。

注意：若两个序列长度不等则视为并不是一个栈的压入、弹出序列。若两个序列都为空，则视为是一个栈的压入、弹出序列。

样例
输入：[1,2,3,4,5]
      [4,5,3,2,1]

输出：true

## 检查合法Stack的弹出序列-总体思路

模拟一遍；

对于每一个pushed序列元素，

对于栈有两个操作：
（1）当前元素入栈
（2）弹出栈。

如果弹出序列的当前元素与栈顶元素相同，则弹出；否则继续入栈。

首先压入第一个元素；

然后紧接着此时栈有两个操作？ 弹出当前元素 或者 继续压入新的元素。

如何区分呢？

要看top与弹出序列的当前是否一致；如果一致，说明弹出了元素； 如果不一致，说明压入了新的元素。

接着再继续比较...

## 检查合法Stack的弹出序列-代码实现

```cpp
class Solution {
public:
/*
[1,2,3,5]
1,2,3, 5, 
q: [4,5,3,1,2]

*/
bool isPopOrder(vector<int> p,vector<int> q) {
        if (p.size() != q.size()) return false;
        stack<int> s;
        int i = 0, j = 0;
        while (j < int(q.size())) {
            if (s.empty() || s.top() != q[j]) {
                if (i == int(p.size())) {
                    return false;
                }
                s.push(p[i++]);
            }
            else {
                s.pop();
                j++;
            }
        }
        return true;
    }
};
```
