---
title: 第一个不重复的字符系列
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 哈希
---

在字符串中找出第一个只出现一次的字符。

如输入"abaccdeff"，则输出b。

如果字符串中不存在只出现一次的字符，返回#字符。

样例：
输入："abaccdeff"

输出：'b'

```cpp
class Solution {
public:
    char firstNotRepeatingChar(string s) {
        map<char, int> counter;
        for (auto x: s) {
            counter[x]++;
        }
        for (auto x: s) {
            if (counter[x] == 1) {
                return x;
            }
        }

        return '#';
    }
};
```

请实现一个函数用来找出字符流中第一个只出现一次的字符。

例如，当从字符流中只读出前两个字符”go”时，第一个只出现一次的字符是’g’。

当从该字符流中读出前六个字符”google”时，第一个只出现一次的字符是’l’。

如果当前字符流没有存在出现一次的字符，返回#字符。

样例
输入："gabcdgle"

输出："ggg#ll"

解释：每当字符流读入一个字符，就进行一次判断并输出当前的第一个只出现一次的字符。

解题思路：

第一个只出现一次，表示顺序，需要有队列。 谁，什么时候入队列？什么时候出队列？
通过map记录次数

goo
