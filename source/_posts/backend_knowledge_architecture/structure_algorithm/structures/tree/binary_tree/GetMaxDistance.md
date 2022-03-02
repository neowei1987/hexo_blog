---
title: 二叉树遍历系列-二叉树最远距离
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
- 二叉树
---

如果我们把二叉树视为一个图，父子节点之间的连线视为双向的，我们姑且定义为“举例”为两节点之间边的个数。写一个程序求一颗二叉树中相距最远的两个节点之间的距离（《编程之美》3.8）

### 解题思路

该题目的技巧在于 全局变量的 应用。

需要克服的惯性思维：更多的题目的计算结果会作为递归函数的返回变量。

这个函数的返回值其实是root节点的高度。

在计算高度的过程中，**顺便**完成全局变量的更新。

### code

```cpp
int GetMaxDistance(TreeNode* root) {
    if (root == NULL) return 0;
    
    int max_distance = INT_MIN;

    dfs(root, INT_MIN);

    return max_distance
}

int dfs(TreeNode* root, int &max_distance) {
    if (root == NULL) return -1;

    int left_max_depth = dfs(root->left, &max_distance);
    int right_max_depth = dfs(root->right, &max_distance);

    int temp_distance = left_max_depth + right_max_depth + 2;

    if (temp_distance > max_distance) max_distance = temp_distance;

    return left_max_depth > right_max_depth ? left_max_depth + 1 : right_max_depth + 1;
}
```