---
title: 杂题系列-打印最小数字
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

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
