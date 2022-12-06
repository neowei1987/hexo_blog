---
title: 分裂二叉树的最大乘积
date: 2022-12-06 22:03:03
updated:
description: 
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 二叉树
---

## 0. 题目

给你一棵二叉树，它的根为 root
请你删除 1 条边，使二叉树分裂成两棵子树
且它们子树和的乘积尽可能大

由于答案可能会很大
请你将结果对 10^9 + 7 取模后再返回

<!-- more -->

## 1. 差的思路

（1）从下往上遍历二叉树，把每一个subtree的sum计算出来，并存到一个map中，key为treeNode*, value为该treeNode的sum

（2）再遍历一遍二叉树，把所有的边（root--right; root--left）遍历出来放到一个容器中

（3）遍历上面的容器，取出每一条的边的两个顶点（必为父子关系）；

对于孩子节点，查map，获取该乘积的左边部分left_sum；

对于父亲节点，查map[root->right] + root本身的val， 获取乘积的右边部分right_sum；

max = max(cur_max, left_sum * right_sum)

## 2. 更好的思路

上面思路中的right_sum还有别的方法可以获取？

启发式思考，**正向思维是做加法，逆向思维是做减法**,right_sum = TotalSum - left_sum

有了上面的思考，我们重新梳理新的思路：

（1）遍历一遍二叉树，获取TotalSum

（2）再自下而上遍历（后序遍历）一遍二叉树，得到当前root的sum（计作cur_sum)， 除了root子树以外的其他节点的sum为TotalSum - cur_sum

（3）max = max(cur_max, cur_sum * (TotalSum - cur_sum))

## 3. 代码实现

```cpp
class Solution {
public:
    long long ans;
    long long sum;
    void dfs1(TreeNode* root){
        if(!root) return ;
        sum += root->val;
        dfs1(root->left);
        dfs1(root->right);
    }
    
    long long dfs2(TreeNode* root){
        if(!root) return 0;
        long long x = dfs2(root->left) + dfs2(root->right) + root->val;
        ans= max(ans, x * (sum - x));
        return x;
    }
    
    int maxProduct(TreeNode* root) {
        ans = 0;
        sum = 0;
        dfs1(root);
        dfs2(root);
        return ans % int(1e9+7);
    }
};
```
