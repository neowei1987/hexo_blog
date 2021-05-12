---
title: 二叉树系列-二叉树镜像
date: 2021-01-05 13:45:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 二叉树
- 剑指Offer
---

## 二叉树镜像-题目描述

输入一个二叉树，将它变换为它的镜像。

样例
输入树：
      8
     / \
    6  10
   / \ / \
  5  7 9 11

 [8,6,10,5,7,9,11,null,null,null,null,null,null,null,null] 
输出树：
      8
     / \
    10  6
   / \ / \
  11 9 7  5

 [8,10,6,11,9,7,5,null,null,null,null,null,null,null,null]

<!-- more -->

## 二叉树镜像-总体思路

这个问题与[判断二叉树是否对称](isSymmetric.html)差别还是蛮大的，一定要注意区分开来。

遍历方式：后序遍历
参数：当前节点
处理逻辑：在完成子节点的迭代之后，swap指针即可。
返回值：当前节点

## 二叉树镜像-代码实现

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
    TreeNode* dfs(TreeNode* root) {
        if (!root) return nullptr;
        
        auto new_left = dfs(root->right);
        auto new_right = dfs(root->left);
        
        root->left = new_left;
        root->right = new_right;
        return root;
    }
    
    void mirror(TreeNode* root) {
       root = dfs(root);
    }
};
```
