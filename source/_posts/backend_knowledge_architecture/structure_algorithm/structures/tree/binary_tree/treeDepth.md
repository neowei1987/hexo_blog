---
title: 二叉树遍历系列-获取树的深度
date: 2021-01-03 23:00:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- 剑指Offer
- [数据结构与算法]
tags: 
- 二叉树
---

## 题目描述

输入一棵二叉树的根结点，求该树的深度。

从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

样例
输入：二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]如下图所示：
    8
   / \
  12  2
     / \
    6   4

输出：3

## 实现思路

第一，我们要搞清楚几个概念：树的深度、一个节点的深度与高度。

第二，我们需要知道：深度是从上往下的，我们需要前序遍历。

第三，我们需要知道：高度是从下往上的，我们需要后序遍历。

最后，根节点比较特殊，树的深度，等于根节点的高度，也就是root到所有leaf的最长路径。

## 代码实现

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int dfs(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(dfs(root->right), dfs(root->left));

    }
    int treeDepth(TreeNode* root) {
        return dfs(root);
    }
};
```