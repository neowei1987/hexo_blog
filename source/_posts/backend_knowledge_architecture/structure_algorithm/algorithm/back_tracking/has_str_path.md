---
title: 回溯-矩阵中找字符串
date: 2021-01-14 17:01:03
mathjax: true
categories:
- 
tags: 
- 
---

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。

路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。

如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。

注意：

输入的路径不为空；
所有出现的字符均为大写英文字母；
样例
matrix=
[
["A","B","C","E"],
["S","F","C","S"],
["A","D","E","E"]
]

str="BCCE" , return "true"

str="ASAE" , return "false"

## 解题思路

状态：<i, j> + 访问位图

选择: 四个方向

路径：该问题不需要

结果集：不需奥

结束条件： 找到任何一个解就可以推出。

## 示例代码

```cpp
class Solution {
public:
    bool dfs(vector<vector<char>>& matrix, string &str, int u, int x, int y) {
        //视频中的错误写法（测试用例不全导致）
        //if (u == str.length()) return true;
        //if (matrix[sx][y] != str[u]) return false;

        //肯定不合适
        if (matrix[x][y] != str[u]) return false;
        //已经到底了，返回ok
        if (u == str.length() - 1) return true; 

        int t = matrix[x][y];
        matrix[x][y] = '#';

        int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < matrix.size() && b >= 0 && b < matrix[a].size()) {
                if (dfs(matrix, str, u + 1, a, b)) return true;
            }
        }

        matrix[x][y] = t;
        return false;
    }

    bool hasPath(vector<vector<char>>& matrix, string &str) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (dfs(matrix, str, 0, i, j))
                {
                    return true;
                }
            }
        }

        return false;
    }
};

```
