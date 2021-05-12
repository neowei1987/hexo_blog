---
title: 二叉树遍历系列-从上往下打印出二叉树的每个结点
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

## 从上往下打印出二叉树，同层从左到右-题目描述

从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。

样例
输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[8, 12, 2, 6, 4]

## 从上往下打印出二叉树，同层从左到右-总体思路

借助queue来实现层次遍历

## 从上往下打印出二叉树，同层从左到右-代码实现

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
 
    vector<int> printFromTopToBottom(TreeNode* root) {
         vector<int> res;
        queue<TreeNode*> q;
    
        if (!root) return res;
        
        q.push(root);
        while (!q.empty()) {
            auto r = q.front();
            q.pop();
            res.push_back(r->val);
            if (r->left) q.push(r->left);
            if (r->right) q.push(r->right); 
        }
        
        return res;
    }
    
};
```

## 从上往下打印出二叉树，同层从左到右，分行打印-题目描述

从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层打印到一行。

样例
输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[[8], [12, 2], [6], [4]]

## 从上往下打印出二叉树，同层从左到右，分行打印-总体思路

相对上题，难点在于如何识别分行，一般而言我们有以下几种办法：
（1）使用nullptr作为分隔符，每次遇到nullptr进行分行处理，并压入新的nullptr
（2）借助size, 每次遍历size个元素，size为上一次压入的元素个数

## 从上往下打印出二叉树，同层从左到右，分行打印-代码实现

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
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        
        if (!root) return res;
        
        q.push(root);
        q.push(nullptr);
        vector<int> level;
        
        while (q.size()) {
            auto t = q.front();
            q.pop();
            
            if (!t) {
                if (level.empty()) break;
                res.push_back(level);
                level.clear();
                q.push(nullptr);
                continue;
            }
            
            level.push_back(t->val);
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
            
        }
    }

     vector<vector<int>> printFromTopToBottom2(TreeNode* root) {
        vector<vector<int>> res;
        vector<int> level;
        queue<TreeNode*> q;
        
        if (!root) return res;
        q.push(root);
        while (q.size()) {
            int qs = q.size();
            for (int i = 0; i < qs; ++i) {
                auto t = q.front();
                q.pop();
                level.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(level);
            level.clear();   
        }
    }
};
```

## 从上往下打印出二叉树，同层从左到右，之字形打印-题目描述

请实现一个函数按照之字形顺序从上向下打印二叉树。

即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

样例
输入如下图所示二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]
    8
   / \
  12  2
     / \
    6   4
输出：[[8], [2, 12], [6, 4]]

## 从上往下打印出二叉树，同层从左到右，之字形打印-总体思路

基于上题，在res加入元素之前，判定res是否奇数，如果是奇数的话，就reverse一下子level数组

## 从上往下打印出二叉树，同层从左到右，之字形打印-代码实现

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
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        
        if (!root) return res;
        
        q.push(root);
        q.push(nullptr);
        vector<int> level;
        
        bool flag = false;
        
        while (q.size()) {
            auto t = q.front();
            q.pop();
            
            if (!t) {
                if (level.empty()) break;
                if (flag) reverse(level.begin(), level.end());
                res.push_back(level);
                level.clear();
                q.push(nullptr);
                flag = !flag;
                continue;
            }
            
            level.push_back(t->val);
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
            
        }
    }

    vector<vector<int>> printFromTopToBottom2(TreeNode* root) {
        vector<vector<int>> res;
        vector<int> level;
        queue<TreeNode*> q;
        
        if (!root) return res;
        q.push(root);
        while (q.size()) {
            int qs = q.size();
            for (int i = 0; i < qs; ++i) {
                auto t = q.front();
                q.pop();
                level.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            if (res.size() % 2) {
                reverse(level.begin(), level.end());
            }
            res.push_back(level);
            level.clear();   
        }
    }
};
```