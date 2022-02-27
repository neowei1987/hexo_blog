---
title: 滑动窗口系列-最长无重复字串
date: 2021-01-05 15:44:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 滑动窗口
- 剑指Offer
---

## 最长无重复字串 - 题目描述

请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

假设字符串中只包含从’a’到’z’的字符。

样例
输入："abcabc"

输出：3

## 最长无重复字串-实现思路

首先，默写下滑动窗口的模版：

```cpp
int i = 0, j = 0, n;
while (i < n) {
    //对新进入窗口的元素i进行处理

    while (j < i && check(xx)) {
        //对出窗口的元素j进行处理
        j++;
    }
}
```

其次，搞清楚滑动窗口是用来做什么的以及用什么数据结构来维护

很明显，我们需要使用滑动窗口来存储每一个字母的出现次数，并且在**当前窗口内的字母不重复**；数据结构的话，hashmap即可。

## 最长无重复字串-代码实现

```cpp
 int longestSubstringWithoutDuplication(string s) {
       int i, j = 0, n =s.size();
       unordered_map<char,int> counter;
       int res = 0;
       while (i < n) {
           char c = s[i];
           counter[c]++;
           if (counter[c] == 1) { //新来了一个不重复元素，则窗口扩大了
                res = max(res, i - j + 1)
           }
           i++;
           while (j < i && counter[c] > 1) { //如果现在窗口已经不在符合条件，则一直往前移动left，直到窗口重新满足
               counter[s[j]]--;
               j++;
           }
       }
    }
```
