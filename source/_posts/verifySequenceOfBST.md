---
title: 二叉树遍历系列-判断该数组是不是某二叉搜索树的后序遍历的结果
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

## 判断该数组是不是某二叉搜索树的后序遍历的结果-题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。

如果是则返回true，否则返回false。

假设输入的数组的任意两个数字都互不相同。

样例
输入：[4, 8, 6, 12, 16, 14, 10]

输出：true

## 判断该数组是不是某二叉搜索树的后序遍历的结果-总体思路

分为几步：
（1）根据后序遍历序列的定义，最右边的元素是中间节点X，并且左子树的元素均小于X，右子树的元素均大于X
（2）顺序扫描，找到左右子树的分割点Y(分割点左边都小于X)
（3）从分割点Y继续扫描，确认是否有bad case，有的话，直接返回不合法
（4）递归处理左右两部分

## 判断该数组是不是某二叉搜索树的后序遍历的结果-代码实现

```cpp
class Solution {
public:
    vector<int> s;
    bool dfs(int l, int r) {
        if (l >= r) return true;
        
        //找到分界点
        int k = l;
        while (k < r && s[k] < s[r]) k++;
        
        //确认分界点之后的元素是否都足够大
        for (int i = k; i< r; ++i) {
            if (s[i] < s[r]) {
                return false;
            }
        }
        
        //递归处理
        return dfs(l, k - 1) && dfs(k, r - 1);
        
    }
    
    bool verifySequenceOfBST(vector<int> sequence) {
        s = sequence;
        if (s.empty()) return true;
        return dfs(0, s.size() - 1);
    }
};
```
