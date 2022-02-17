---
title: 骰子的点数
date: 2020-12-27 23:22:03
mathjax: true
categories:
- 剑指Offer
tags: 
- DFS
- 线性DP
---

## 题目描述

将一个骰子投掷n次，获得的总点数为s，s的可能范围为n~6n。

掷出某一点数，可能有多种掷法，例如投掷2次，掷出3点，共有[1,2],[2,1]两种掷法。

请求出投掷n次，掷出n~6n点分别有多少种掷法。

样例1
输入：n=1

输出：[1, 1, 1, 1, 1, 1]

解释：投掷1次，可能出现的点数为1-6，共计6种。每种点数都只有1种掷法。所以输出[1, 1, 1, 1, 1, 1]。
样例2
输入：n=2

输出：[1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1]

解释：投掷2次，可能出现的点数为2-12，共计11种。每种点数可能掷法数目分别为1,2,3,4,5,6,5,4,3,2,1。

所以输出[1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1]。

## 思路

1. DFS
2. 因为有很多重复计算，所以考虑用DP来优化，状态转移方程：
   $$f[i][j] = \sum\limits_{k=1}^{6}f[i-1][j-k]$$

## DFS代码

```cpp
class Solution {
public:
    vector<int> path;
    vector<int> res;

    void dfs(int n, int sum) {
        if (n == 0) {
            res[sum]++;
            return;
        }

        for (int i = 1; i <= 6; ++i) {
            dfs(n - 1, sum + i);
        }
    }

    vector<int> numberOfDice(int n) {
        res.resize(6 * n + 1);
        dfs(n, 0);

        vector<int> ret;
        for (auto x : res) {
            if (x > 0) ret.push_back(x);
        }

        return ret;
    }
};
```
