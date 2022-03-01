---
title: 二叉搜索树遍历-获取第k个节点
date: 2021-01-03 19:47:03
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

给定一棵二叉搜索树，请找出其中的第k小的结点。

你可以假设树和k都存在，并且1≤k≤树的总结点数。

样例
输入：root = [2, 1, 3, null, null, null, null] k = 3

输出：3

## 实现思路

首先，我们需要有一个认知：二叉搜索树等同于一个有序数组。

然后基于上面的认知去思考：我如何在一个有序数组中找到第k小的元素。

所以，我们需要中序遍历BST，在遍历过程中对访问的元素进行计数即可，当计数到k时，便是我们要找的元素。

这里科普一个常识：**对于BST，我们一定是中序遍历**！否则就浪费了BST有序的特性了。

## 代码实现

``` cpp
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
    int k;
    TreeNode* dfs(TreeNode* root) {
        if (root->left) {
            auto r = dfs(root->left);
            if (r) return r;
        }
        if (--k == 0) return root;

        if (root->right) return dfs(root->right);
        return nullptr;
    }

    TreeNode* kthNode(TreeNode* root, int _k) {
        k = _k;
        return dfs(root);    
    }
};
```
