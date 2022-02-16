---
title: 数组系列-从外向里以顺时针的顺序打印矩阵
date: 2021-01-05 13:42:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 数组
- 剑指Offer
---

## 从外向里以顺时针的顺序打印矩阵-题目描述

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

样例
输入：
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]

输出：[1,2,3,4,8,12,11,10,9,5,6,7]

<!-- more -->

## 从外向里以顺时针的顺序打印矩阵-总体思路

该题目的核心考察点在于：方向数组的应用

```cpp
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (int d = 0; d < 4; d++) {
        //do sth
    }
```

另一个考察点是访问bitmap的使用。

## 从外向里以顺时针的顺序打印矩阵-代码实现

```cpp
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        int rows = matrix.size();
        if (!rows)  return res;
        int cols = matrix[0].size();
        if (!cols) return res;
        
        vector<int> visited(rows * cols + 1, false);
        
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        for (int i = 0, j = 0, d = 0, k = 0; k < rows * cols; ++k) {
            res.push_back(matrix[i][j]);
            visited[i * cols + j] = true;
            i += dx[d], j += dy[d];
            if (i < 0 || i >= rows || j < 0 || j >= cols || visited[i * cols + j]) {
                i -= dx[d], j-=dy[d]; //撤销原来走的路
                d = (d + 1) % 4;    //改变方向
                i += dx[d], j += dy[d]; //重新走一遍
            }
        }
        
        return res;
    }
};
```
