---
title: 二叉树遍历系列-二叉搜索树转有序双向链表
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
- 剑指Offer
---

## 二叉搜索树转有序双向链表-题目描述

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。

要求不能创建任何新的结点，只能调整树中结点指针的指向。

注意：

需要返回双向链表最左侧的节点。
例如，输入下图中左边的二叉搜索树，则输出右边的排序双向链表。

## 二叉搜索树转有序双向链表-总体思路

两种思路：

第一种思路，dfs的主要任务是返回子树对应链表的头尾节点；按照这种思路的话，我们的遍历方式是后序遍历。

第二种思路，dfs的主要任务就是按照顺序访问到每一个node，同时记录一个全局的pre，然后将pre与node建立双向关联即可。

## 二叉搜索树转有序双向链表-代码实现

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
pair<Node*, Node*> dfs(Node* root) {
    if (!(root->left) && !(root->right)) {
        root->left = root;
        root->right = root;
        return {root, root};
    }
    
    //访问左边
    pair<Node*, Node*>  left = {root, root};
    if (root->left) {
        left = dfs(root->left);
    }

    //访问右边
    pair<Node*, Node*>  right = {root, root};
    
    if (root->right) {
        right = dfs(root->right);
    }

    //访问中间节点
    if (left.first != root) {
        left.second->right = root;
        root->left = left.second;
    }

    if (right.first != root) {
        root->right = right.first;
        right.first->left = root;
    }
 
    return {left.first, right.second};
}
```

```cpp
 void  dfs(Node* root) {
        if (!root) return;
        
        //访问左边
        dfs(root->left);

        //中序遍历
        if (!pre) {
            head = root;
        }
        else {
            pre->right = root;
            root->left = pre;
        }
        pre = root;

        //访问右边
        dfs(root->right);
    }
```
