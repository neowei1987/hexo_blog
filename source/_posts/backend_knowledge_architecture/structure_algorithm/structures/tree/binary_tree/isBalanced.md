---
title: 二叉树遍历系列-判定是否平衡树
date: 2021-01-03 23:00:03
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

## 题目描述

输入一棵二叉树的根结点，判断该树是不是平衡二叉树。

如果某二叉树中任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

注意：

规定空树也是一棵平衡二叉树。
样例
输入：二叉树[5,7,11,null,null,12,9,null,null,null,null]如下所示，
    5
   / \
  7  11
    /  \
   12   9

输出：true

## 实现思路

第一，我们要搞清楚几个概念：树的深度、一个节点的深度与高度。

第二，我们需要知道：深度是从上往下的，我们需要前序遍历。

第三，我们需要知道：高度是从下往上的，我们需要后序遍历。

最后，根节点比较特殊，树的深度，等于根节点的高度，也就是root到所有leaf的最长路径。

综上，该题目还是后序遍历。

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
 * 
 */
 
typedef pair<bool, int> PBI;
 
class Solution {
public:
    
    PBI dfs(TreeNode* root) {
        if (!root) return {true, 0};

        auto lbi = dfs(root->left);
        if (!lbi.first) return {false, 0};

        auto rbi = dfs(root->right);
        if (!rbi.first) return {false, 0};

        if (abs(lbi.second - rbi.second) > 1) {
            return {false, 0};
        } 
        else {
            return {true, 1 + max(lbi.second, rbi.second)};
        }
    }

    bool isBalanced(TreeNode* root) {
        return dfs(root).first;
    }
};
```
