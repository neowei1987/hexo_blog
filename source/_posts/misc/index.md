---
title: 数字计算相关的杂题
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

## 数字相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [atoi](../atoi.html)  |累乘技巧|
| | [幂次方](./power.html)  |快速幂|
| | [获取丢失的数字](../getMissingNumber.html)  |逆向思维-补齐|
| | [特殊的累加](../special_acc.html)  |奇技淫巧-缺乏一般性|
| | [字符串反转问题](../string_reverse.html)  |翻手法则|

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

例如输入数组[3, 32, 321]，则打印出这3个数字能排成的最小数字321323。

样例
输入：[3, 32, 321]

输出：321323
注意：输出数字的格式为字符串。

```cpp
class Solution {
public:
    
    static int compare(int a, int b) {
        string ab = to_string(a) + to_string(b);
        string ba = to_string(b) + to_string(a);
        return ab < ba;
    }
    
    string printMinNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), compare);   
        
        string res;
        for (auto x : nums) {
            res += to_string(x);
        }
        return res;
    }
};
```

请实现一个函数，把字符串中的每个空格替换成"%20"。

你可以假定输入字符串的长度最大是1000。
注意输出字符串的长度可能大于1000。

样例
输入："We are happy."

输出："We%20are%20happy."

```cpp
class Solution {
public:
    string replaceSpaces(string &str) {
        string r;
        for (auto x : str) {
            if (x != ' ') r += x;
            else r += "%20";
        }
        return r;
    }
};
```

输入一个整数 n ，求斐波那契数列的第 n 项。

假定从0开始，第0项为0。(n<=39)

样例
输入整数 n=5

返回 5

```cpp
class Solution {
public:
    int Fibonacci(int n) {
        int a = 0;
        int b = 1;
        int r = 0;
        
        while (n--) {
            r = a + b;
            a = b;
            b = r;
        }
        
        return a;
    }
};
```

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
