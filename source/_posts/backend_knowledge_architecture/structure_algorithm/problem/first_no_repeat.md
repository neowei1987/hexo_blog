---
title: 第一个不重复的字符系列
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 剑指Offer
- 数据结构与算法
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
输入："google"

输出："ggg#ll"

解释：每当字符流读入一个字符，就进行一次判断并输出当前的第一个只出现一次的字符。

解题思路：

创建一个长度为256的整形数组，每个字符根据其ASCLL码值作为数组的下标。数组的初始值都为0，数组存储的是字符在字符流中的位置，从1开始。

如果某个字符之前没出现过，则occurrence[i]==0,若出现过，则occurrence[i]>0。当某个出现过的字符再次出现时，由于occurrence[i]>0,此时可以把occurrence[i]赋值为-1，因为这个字符出现了2次，可以不用再考虑了。

接着遍历数组，找出第一次出现的不重复的字符。
