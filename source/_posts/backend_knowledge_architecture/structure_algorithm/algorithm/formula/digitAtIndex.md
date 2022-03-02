---
title: 找递增序列下标数字
date: 2020-12-27 23:42:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
---

数字以0123456789101112131415…的格式序列化到一个字符序列中。

在这个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数求任意位对应的数字。

样例
输入：13

输出：1

```cpp

class Solution {
public:
    int digitAtIndex(int n) {
        if(n<=9){
            return n;
        }
        int len = 1;
        long count = 9;
        int start = 1;
        while(n>len*count){
            n-=len*count;
            len+=1;
            count*=10;
            start *= 10;
        }
        start += (n-1)/len;
        string str = to_string(start);
        return str[(n-1)%len]-48;
    }
};

```