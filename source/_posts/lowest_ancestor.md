---
title:  二叉树遍历系列-最低公共祖先
date: 2021-01-03 20:47:03
updated:
copyright: true
password:
keywords: [奇技淫巧]
description: 
mathjax: true
categories:
tags: 
---

## 题目描述

给出一个二叉树，输入两个树节点，求它们的最低公共祖先。

一个树节点的祖先节点包括它本身。

注意：

输入的二叉树不为空；
输入的两个节点一定不为空，且是二叉树中的节点；
样例
二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]如下图所示：
    8
   / \
  12  2
     / \
    6   4

1. 如果输入的树节点为2和12，则输出的最低公共祖先为树节点8。

2. 如果输入的树节点为2和6，则输出的最低公共祖先为树节点2。

## 最普通的实现思路

实现考虑容易想到的实现思路：
第一步，找到从root到节点A的路径，计作pa；时间复杂度$O(n)$，空间复杂度$O(n)$
第二步，找到从root到节点B的路径，计作pb；时间复杂度$O(n)$，空间复杂度$O(n)$
第三步，同时遍历pa、pb，找到最后一个相同的元素，便是A、B的最低公共祖先。时间复杂度$O(n)$

综上，总的时间复杂度为$O(3n)$，空间复杂度$O(2n)$

## 常规的二叉树遍历讨论

拿到一个二叉树遍历的题目，
（1）我们首先要思考的是：要解决这个问题，哪种遍历方式最合适？
前序遍历、后序遍历、中序遍历还是层次遍历？
（2）其次，我们做出一个假设：假设我已经调用了dfs(child),并解决了这个子问题
（3）最后，基于上面的假设去思考如何解决整个问题。

针对上面的第一个问题，我们想要从下往上遍历整棵树，所以我们需要后序遍历。
同时我们做出假设，dfs(child,p,q)会返回p,q在child子树中的最低公共祖先。那么我们的代码大概会长这样：

```cpp
TreeNod* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
    //基本情况
    TreeNode* left = dfs(root->left, p, q);
    TreeNode* right = dfs(root->right, p, q);
    //更多处理：要充分理解题目的要求，明确每一个概念的定义，将其转换为代码。
}
```

如果在left中找到了p/q， 并且在right中也找到了p/q, 那么显然root就是最低公共祖先。
如果left中p/q, 而right没有找到，显然遍历left得到的返回值就是最低公公祖先。

## 最终代码

```cpp
TreeNod* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == p || root == q || root == null) return root;
    TreeNode* left = dfs(root->left, p, q);
    TreeNode* right = dfs(root->right, p, q);
    if (left && right) return root;
    if (left) return left; else return right;
}
```
