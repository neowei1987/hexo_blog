---
title: 奇技淫巧-特殊的累加
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

求1+2+…+n,要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

样例
输入：10

输出：55

## 思路

**常用技巧**： 通过!n来判定n是否等于0

## 代码

```cpp
typedef int (*handler)(int);
handler fn[2]; 

int dfs(int n) {
    handler myfn= fn[!!n];
    return myfn(n);
}

int dfs_base(int n) {
    return 0;    
}

int dfs_normal(int n) {
    return n + dfs(n - 1);
}

class Solution {
public:
    int getSum(int n) {
        fn[0] = dfs_base;
        fn[1] = dfs_normal;
        return dfs(n);
    }
};

```
