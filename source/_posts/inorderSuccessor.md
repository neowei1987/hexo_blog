---
title: 二叉树遍历系列-中序遍历序列的下一个节点
date: 2021-01-04 11:42:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags: 
---

## 中序遍历序列的下一个节点-题目描述

给定一棵二叉树的其中一个节点，请找出中序遍历序列的下一个节点。

注意：

如果给定的节点是中序遍历序列的最后一个，则返回空节点;
二叉树一定不为空，且给定的节点一定不是空节点；
样例
假定二叉树是：[2, 1, 3, null, null, null, null]， 给出的是值等于2的节点。

则应返回值等于3的节点。

解释：该二叉树的结构如下，2的后继节点是3。
  2
 / \
1   3

## 中序遍历序列的下一个节点-总体思路

需要我们明确中序遍历的定义
模拟题
其实模拟题就是分情况讨论。

## 中序遍历序列的下一个节点-代码实现

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *father;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* p) {
        if (p->right) {
            p = p->right;
            while (p->left) p = p->left;
            return p;
        }
        
        while (p->father && p->father->left != p) p = p->father;
        return p->father;
    }
};
```
