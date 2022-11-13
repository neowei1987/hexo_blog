---
title: 贪心-分糖果问题
date: 2022-11-14 22:58:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 贪心
---

一群孩子做游戏，现在请你根据游戏得分来发糖果，要求如下：

1. 每个孩子不管得分多少，起码分到一个糖果。
2. 任意两个相邻的孩子之间，得分较多的孩子必须拿多一些糖果。(若相同则无此限制)

给定一个数组 arrarr 代表得分数组，请返回最少需要多少糖果。

要求: 时间复杂度为 O(n)O(n) 空间复杂度为 O(n)O(n)

```cpp

class Solution {
public:
    /**
     * pick candy
     * @param arr int整型vector the array
     * @return int整型
     */
    int candy(vector<int>& arr) {
        //正向遍历一次，满足了中间大于左边时的要求；
        vector<int> s(arr.size(), 1);
        for (int i = 1;i < arr.size(); i++){
            if (arr[i] > arr[i - 1]) {
                s[i] = s[i - 1] + 1;
            }
        }

        //逆向遍历一遍，继续满足中间大于右边时的要求
        for (int i = arr.size() - 2; i >= 0; i--) {
            if (arr[i] > arr[i + 1] && s[i] <= s[i + 1]) {
                s[i] = s[i + 1] + 1;
            }
        }

        int res = 0;
        for (auto x : s) {
            res += x;
        }

        return res;
    }
};
```