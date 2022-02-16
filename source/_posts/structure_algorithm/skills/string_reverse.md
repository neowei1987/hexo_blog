---
title: 翻手法则-字符串反转问题
date: 2021-01-03 23:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 剑指Offer
---

## 反转单词-题目描述

输入一个英文句子，单词之前用一个空格隔开，且句首和句尾没有多余空格。翻转句子中单词的顺序，但单词内字符的顺序不变。

为简单起见，标点符号和普通字母一样处理。

例如输入字符串"I am a student."，则输出"student. a am I"。

样例
输入："I am a student."

输出："student. a am I"

## 反转单词-代码实现

```cpp
class Solution {
public:
    void reverse(string& s, int i, int j) {
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
    
    string reverseWords(string s) {
        int i = 0, j = 0;
        while (s[j] != '\0') {
            if (s[j] == ' ') {
                reverse(s, i, j - 1); //反转每一个
                i = j + 1;
            }
            j++;
        }
        reverse(s, i, j - 1); //处理上面的最后一次循环

        //整体反转一次
        reverse(s, 0, j - 1);
        return s;
    }
};
```

## 字符串左旋转-题目描述

字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。

请定义一个函数实现字符串左旋转操作的功能。

比如输入字符串"abcdefg"和数字2，该函数将返回左旋转2位得到的结果"cdefgab"。

注意：

数据保证n小于等于输入字符串的长度。
样例
输入："abcdefg" , n=2

输出："cdefgab"

## 字符串左旋转-代码实现

```cpp
class Solution {
public:
    void reverse(string& s, int i, int j ) {
        //对撞指针，往中间凑
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
    string leftRotateString(string str, int k) {
        int n = str.size();
        if (k == 0) return str;
        
        reverse(str, 0, k - 1);
        reverse(str, k, n - 1);
        reverse(str, 0, n - 1);
        return str;
    }
};
```
