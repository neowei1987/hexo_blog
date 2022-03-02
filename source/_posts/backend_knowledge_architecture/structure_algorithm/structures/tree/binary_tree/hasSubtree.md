---
title: 二叉树系列-二叉树子结构
date: 2021-01-05 14:30:03
updated:
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 二叉树
---

## 二叉树子结构-题目描述

输入两棵二叉树A，B，判断B是不是A的子结构。

我们规定空树不是任何树的子结构。

样例
树A：

     8
    / \
   8   7
  / \
 9   2
    / \
   4   7
树B：

   8
  / \
 9   2
返回 true ,因为B是A的子结构。

<!-- more -->

## 二叉树子结构-总体思路

明确一下子结构匹配的三种情况：

（1）当前子树与Target匹配

（2）当前子树的右子树与Target匹配

（3）当前子树的左子树与Target匹配

遍历方式：先序遍历

参数：两棵子树的根节点

base condition: nullptr判定

处理逻辑：

（1）重点考虑是否覆盖了所有的子结构匹配的情况

返回值：是否匹配

## 二叉树子结构-代码实现

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
    bool hasSubtree(TreeNode* r1, TreeNode* r2) {
        if (!r2) {return false;}
        
        if (!r1)  return false;
        
        //如果当前节点不匹配，需要继续遍历子树；而不是返回
        if (r1->val == r2->val) {
            bool ret = true;
            if (r2->left || r2->right) {
                ret = (r2->left ? (hasSubtree(r1->left, r2->left)) : true) && (r2->right ? hasSubtree(r1->right, r2->right) : true);
            }
            if (ret) return ret;
        }

        return hasSubtree(r1->left, r2) || hasSubtree(r1->right, r2);
     }
};
```
