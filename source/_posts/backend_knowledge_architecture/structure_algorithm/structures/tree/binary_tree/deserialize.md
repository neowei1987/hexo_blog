---
title: 二叉树遍历系列-二叉树的序列化与反序列化
date: 2021-01-04 17:42:03
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

## 二叉树的序列化与反序列化-题目描述

请实现两个函数，分别用来序列化和反序列化二叉树。

您需要确保二叉树可以序列化为字符串，并且可以将此字符串反序列化为原始树结构。

样例
你可以序列化如下的二叉树
    8
   / \
  12  2
     / \
    6   4

为："[8, 12, 2, null, null, 6, 4, null, null, null, null]"
注意:

以上的格式是AcWing序列化二叉树的方式，你不必一定按照此格式，所以可以设计出一些新的构造方式

## 中二叉树的序列化与反序列化-总体思路

重点考虑反序列化，我们需要考虑一种很容易找到root节点的遍历方式。

如果我无法找到root节点，是无法通过递归来完成反序列化的。

在前中后三种遍历中，我们可以选择先序遍历。 先序遍历，最容易找到root节点

## 中二叉树的序列化与反序列化-代码实现

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
    string s;
    
    void dfs_s(TreeNode* root, string& res) {
        if (!root) {
            res += "null ";
            return;
        }
        
        res += (to_string(root->val) + " ");
        dfs_s(root->left, res);
        dfs_s(root->right, res);
    }
    
    
    //1, 2, 4, 5, 6, null, null, null
    TreeNode* dfs_us(int& u) {
        if (u >= s.size()) {
            return NULL;
        }
        
        //如果是nullptr
        if (s[u] == 'n') {
            u += 5;
            return nullptr;
        }
        
        //如果是有意义的内容
        int val = 0;
        int flag = 1;
        if (s[u] == '-') {flag = -1; u++;}
        while (s[u] != ' ') {
            val = val * 10 + s[u++] - '0';
        }
        val *= flag;
        u++;
        
        //上面都是处理当前节点
        
        auto r = new TreeNode(val);
        auto left = dfs_us(u); //处理左边
        auto right = dfs_us(u);
        r->left =left, r->right = right;
        return r;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        dfs_s(root, res);
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        s = data;
        int c = 0;
        return dfs_us(c);
    }
};
```
