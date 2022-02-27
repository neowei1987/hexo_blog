---
title: 杂题系列-空格替换
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

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