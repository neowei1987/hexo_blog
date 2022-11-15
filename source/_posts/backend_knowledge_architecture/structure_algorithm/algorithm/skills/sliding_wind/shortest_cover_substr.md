---
title: 滑动窗口系列-最短覆盖子串
date: 2021-01-05 15:44:03
updated:
copyright: true
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 滑动窗口
---

```cpp

class Solution {
public:
    unordered_map<char, int> pattern;

    string minWindow(string src, string tt) {
        //将目标串转换为方便检查处理的hashmap
        for (auto x : tt) {
            pattern[x]++;
        }
        int cnt = pattern.size();

        string res;
        for (int i = 0, j = 0, c = 0; i < src.size(); ++i) {
            if (pattern[src[i]] == 1 ) c++;
            pattern[src[i]]--; //将src[i]标记为缺少状态
            //满足了，并且某一个字符是缺的【非pattern中的字符一定缺；并且一定会被补上】，则往前移动
            while (c == cnt && pattern[src[j]] < 0) {
                pattern[src[j++]]++; 
            } 
            if (c == cnt) {
                if (res.empty() || res.size() > i - j + 1) res = src.substr(j, i - j + 1);
            }
        }
        return res;
    }
};
```