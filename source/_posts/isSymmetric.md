---
title: 二叉树系列-判断二叉树是否对称
date: 2021-01-05 13:45:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 二叉树
- 剑指Offer
---

## 判断二叉树是否对称-题目描述

请实现一个函数，用来判断一棵二叉树是不是对称的。

如果一棵二叉树和它的镜像一样，那么它是对称的。

样例
如下图所示二叉树[1,2,2,3,4,4,3,null,null,null,null,null,null,null,null]为对称二叉树：
    1
   / \
  2   2
 / \ / \
3  4 4  3

如下图所示二叉树[1,2,2,null,4,4,3,null,null,null,null,null,null]不是对称二叉树：
    1
   / \
  2   2
   \ / \
   4 4  3

<!-- more -->

## 判断二叉树是否对称-总体思路

这个问题比较tricky的地方在于：根节点的处理是不同于其他节点呢？
那么为什么root节点比较特殊呢？ 根因在于：对称轴便是在于root上，root一定是一个特例！

想明白这一点之后，自然就是遍历顺序了：前序遍历

## 判断二叉树是否对称-代码实现

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
    bool isSymmetric(TreeNode* root) {
        /*
        这么写会segment fault? why?
        if (!root) true;
        return dfs(root->left, root->right);
        */
        return !root || dfs(root->left, root->right);
    }
    
    bool dfs(TreeNode* p1, TreeNode* p2) {
        if (!p1 || !p2) return !p1 && !p2;
        
        //cout << p1 << p2 << endl;
        if (p1->val != p2->val) return false;
        
        return dfs(p1->left, p2->right) && dfs(p1->right, p2->left);
    }
};
```
