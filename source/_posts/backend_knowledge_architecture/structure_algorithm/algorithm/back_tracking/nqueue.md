---
title: 回溯-N皇后问题
date: 2022-11-13 17:01:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 回溯
---

状态：已经填好的行数，每一行填在了哪些位置

选择: 最多N种选择

路径：放置了Queue的<u,j>位置的列表；

结果集：列表的列表

结束条件： 已经把所有的行数填写完；

```cpp
class Solution {
public:
    int res;
    int Nqueen(int n) {
        res = 0;
        dfs(0, n, 0, 0, 0);
        return res;
    }

    void dfs(int u, int n, int col, int pie, int na) {
        if (u == n) {
            res++;
            return;
        }

        for (int j = 0; j < n; ++j) {
            //用位运算来记录状态
            //注意对角线的技巧
            //左上 y = x + b;  b = (y - x + N) 来表现一条线！！
            //右下 y = -x + b; b = (y + x) 来表现一条线！！
            if ((col & 1 << j) || (pie & (1 << (n + u - j))) || (na & (1 << (u + j))))
                continue;
            //col，pie，na都是局部变量，不用保存现场
            dfs(u + 1, n, col | (1 << j), pie | (1 << (n + u - j)), na  | (1 << (u + j)));
        }
    }
};
```
