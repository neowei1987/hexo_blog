---
title: 二叉树遍历系列-二叉树中结点值的和为输入整数的所有路径
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

## 二叉树中结点值的和为输入整数的所有路径-题目描述

输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。

从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

样例
给出二叉树如下所示，并给出num=22。
      5
     / \
    4   6
   /   / \
  12  13  6
 /  \    / \
9    1  5   1

输出：[[5,4,12,1],[5,6,6,5]]

## 二叉树中结点值的和为输入整数的所有路径-总体思路

这里，我在下面的代码中写了很多种写法，我们需要好好体会以下几个点：

（1）我的return条件是什么？（是遇到空节点return还是遇到叶子结点return)

（2）我应该如何处理当前访问到的节点

（2）我应该如何还原现场（是pop一次还是pop两次）

（3）return条件与还原现场的关系是什么？

## 二叉树中结点值的和为输入整数的所有路径-代码实现

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
    vector<vector<int>> res;
    vector<int> path;
    
    //一种写法【正确】---如果到达空节点，则返回
    void dfs(TreeNode* root, int sum) {
        if (!root) return;
        
        path.push_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right && !sum) {
            res.push_back(path);
            //这里不会return;
            //假设最后一个叶子结点是一个错误答案，我们显然需要把这个节点pop出来？
            //那我pop的时机是什么呢？ 显然是在遍历完左右子树之后再pop出来。
        }
       
        dfs(root->left, sum);
        dfs(root->right, sum);
        path.pop_back();
    }
    
    //一种正确的写法：注意这里，非叶子节点才会被push进去，所以只需要pop一次；
    void dfs(TreeNode* root, int sum) {
        //结束条件
        if (!root->left && !root->right) { 
            if (sum == root->val) {
                path.push_back(root->val);
                ret.push_back(path);
                path.pop_back();
            }
            return;
        }

        path.push_back(root->val);
        if (root->left) dfs(root->left, sum - root->val);
        if (root->right) dfs(root->right, sum- root->val);
        path.pop_back();
    }


    //另一种正确的写法---如果到达叶子节点，则返回
     void dfs2(TreeNode* root, int sum) {
        path.push_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right) {
            if (!sum) {
                res.push_back(path);
            }  
            return; //注意这里有一个return
            //注意这里return了，现在path中有一个错误的节点，我这个节点需要什么时候pop出来呢？
            //显然只能在外层调用的时候。
        }
       
        if (root->left) {
            dfs(root->left, sum);
            path.pop_back();
        }

        if (root->right) {
            dfs(root->right, sum);
            path.pop_back();
        }
    }

     //错误的写法---如果到达叶子节点，则返回; 但是只pop了一次！！！
     void dfs3(TreeNode* root, int sum) {
        path.push_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right) {
            if (!sum) {
                res.push_back(path);
            } 
            return;  //注意这里有一个return
        }
       
        if (root->left) {
            dfs(root->left, sum);
        }

        if (root->right) {
            dfs(root->right, sum);
        }

        path.pop_back();
    }
    
    vector<vector<int>> findPath(TreeNode* root, int sum) {
        dfs(root, sum);
        return res;
    }
};
```