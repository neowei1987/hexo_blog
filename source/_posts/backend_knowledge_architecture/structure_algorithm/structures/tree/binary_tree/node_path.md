---
title: 二叉树系列-节点路径计算
date: 2021-03-01 13:22:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 二叉树
---

给一个二叉树节点，打印节点路径


###  解题思路

退出条件：找到对应节点

遍历方式：后续遍历

### 

```cpp

void dfs() {
    if (root == target) {
        res.push_back(target);
        return;
    }

    dfs(root->left);
    dfs(root->right);

    if (!res.empty()) && (res.back() == root->left || res.back() == root->right)) {
        res.push_back(root);
    }
}

```


