---
title: 幂次方
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

实现函数double Power(double base, int exponent)，求base的 exponent次方。

不得使用库函数，同时不需要考虑大数问题。

注意：

不会出现底数和指数同为0的情况
当底数为0时，指数一定为正
样例1
输入：10 ，2

输出：100
样例2
输入：10 ，-2  

输出：0.01

```cpp
class Solution {
public:
    double Power(double base, int e) {
        if (e < 0) {
            return 1.0 / Power(base, -e); 
        }
        
        double res = 1.0;
        double t = base;
        while (e) {
            if (e & 1) res = res * t;
            t = t * t;
            e >>= 1; //执行次数是1不同于e = e & (e - 1)
            
        }
        
        /*
        double res = 1.0;
        for (int i = 0; i < e; ++i) {
            res *= base;
        }
        */
        return res;
    }
    
};
```