---
title: 前缀和系列-不使用除法的特殊累乘
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

## 题目描述

给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其中B中的元素B[i]=A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。

不能使用除法。

## 暴力做法

时间复杂度：$O(n^2)$

空间复杂度：除结果数组外，$O(1)$

```cpp
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> res(A.size(), 1);
        
        //i表示要计算的B数组的下标
        for (int i = 0; i < A.size(); ++i) {
            int multi = 1;
            //j表示A数组的下标，下面的循环是做累乘
            for (int j = 0; j < A.size(); j++ ) {
                if (i != i) {
                    multi *= A[i];
                }
            }
            res[i] = multi;
        }        
        return res;
    }
};
```

## 优化思路

**前缀和思想**:当需要多次计算从i到j的累加和时，我们可以考虑计算序列的前缀和序列，把i到j的累加和转换为前缀和序列中i,j下标的元素之差。

**重复计算必可优化原则**：当一套解法中存在重复计算时，我们总是可以依照**空间换时间**原则，将可能存在重复的计算结果存下来。存下来之后，算法的执行效率便提升了。

注意到，前面的暴力解法中，对于i与i+1两个下标的计算，总是会重复计算A[1]到A[i]，我们是否可以仅计算一次呢？

## 时间优化版代码

时间复杂度：$O(n)$

空间复杂度：除结果数组外，$O(n)$

```cpp
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> res(A.size(), 1);
        
        vector<int> pre_part(A.size(), 1); //前半部分的累乘结果
        for (int i = 1; i < A.size(); ++i) {
            pre_part[i] = pre_part[i - 1] * A[i - 1];
        }

        vector<int> post_part(A.size(), 1); //后半部分的累乘结果
        for (int i = A.size() - 2; i >= 0; --i) {
            post_part[i] = post_part[i + 1] * A[i + 1];
        }

         //i表示要计算的B数组的下标
        for (int i = 0; i < A.size(); ++i) {
            res[i] = pre_part[i - 1] * post_part[i + 1];
        }   
        
        return res;
    }
};
```

## 进一步优化思路

考虑上面代码中的第3步，res[i]的计算仅与pre_part数组中的i - 1项有关，我们是否可以把pre_part的计算结果存放在res中呢？

如果把第3步的迭代顺序反一下，那么第2部分与第3部分的迭代顺序就一致了。并且post_part[i]仅与前一项有关，我们可以做**空间压缩**（动态规划背包问题的常见套路），仅使用一个变量即可。

## 空间优化版代码

时间复杂度：$O(n)$

空间复杂度：除结果数组外，$O(1)$

```cpp
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> res(A.size(), 1);
        
        //先将前半部分的计算结果存起来
        for (int i = 1; i < A.size(); ++i) {
            res[i] = res[i - 1] * A[i - 1];
        }

        //逆序遍历，只用一个变量multi来存储后半部分的计算结果。
        for (int i = A.size() - 2; i >= 0; --i) {
            multi = multi * A[i + 1];
            res[i] = res[i - 1] * multi;
        }
 
        return res;
    }
};
```
