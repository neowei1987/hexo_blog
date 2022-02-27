---
title: 杂题系列-字符串转换成整数
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

## 题目描述

请你写一个函数StrToInt，实现把字符串转换成整数这个功能。

当然，不能使用atoi或者其他类似的库函数。

样例
输入："123"

输出：123
注意:

你的函数应满足下列条件：

忽略所有行首空格，找到第一个非空格字符，可以是 ‘+/−’ 表示是正数或者负数，紧随其后找到最长的一串连续数字，将其解析成一个整数；
整数后可能有任意非数字字符，请将其忽略；
如果整数长度为0，则返回0；
如果整数大于INT_MAX(2^31 − 1)，请返回INT_MAX；如果整数小于INT_MIN(−2^31) ，请返回INT_MIN；

## 常规解法

我们先遍历一遍，找到字符串的长度，从而得出最高位的权重(10的几次方？)
然后再遍历一遍，进行累加计算。
时间复杂度：$O(2n)$

## 优化思路

我们可以在一遍搞定，每遍历到一个新的元素，需要做的步骤是：

(1) sum *= 10

(2) sum += NewElement

新的时间复杂度：$O(n)$

该题目其他部分无非就是模拟了，做模拟题目的时候切记思路清晰。

## 优化版代码

```cpp
class Solution {
public:
    int strToInt(string s) {
        int i = 0;
        int sign = 1;
        bool has_num = false;
        long long val = 0;
        while (s[i]) {
            if (s[i] == ' ') {}
            else if (s[i] == '+'  || s[i] == '-') {
                if (!has_num) {
                    sign = s[i] == '+' ? 1 : -1;
                }
            } else if (s[i] >= '0' && s[i] <= '9') {
                has_num = true;
                val = val * 10 + (s[i] - '0');
                if (sign * val > INT_MAX) {return INT_MAX;}
                if (sign * val < INT_MIN) {return INT_MIN;}
            }
            else {
                if (!has_num) {
                    return 0;
                }
            }
            i++;
        }
        
        return sign * val;
    }
    
};
```
