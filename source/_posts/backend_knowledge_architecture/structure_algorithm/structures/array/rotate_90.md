---
title: 矩阵旋转90度
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
categories:
- 数据结构与算法
tags: 
---

矩阵90度旋转

<!-- more -->

```cpp
class Solution {
public:
    vector<vector<int> > rotateMatrix(vector<vector<int> > mat, int n) {
        //水平翻转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(mat[i][j], mat[n - 1 - i][j]);
            }
        }

        //对角线翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        return mat;
    }
};
```
