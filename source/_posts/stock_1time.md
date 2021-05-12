---
title: 股票买卖系列-仅买卖一次
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
keywords: [股票买卖,贪心算法]
description: 
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 剑指Offer
---

## 题目描述

假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖 一次 该股票可能获得的利润是多少？

例如一只股票在某些时间节点的价格为[9, 11, 8, 5, 7, 12, 16, 14]。

如果我们能在价格为5的时候买入并在价格为16时卖出，则能收获最大的利润11。

样例
输入：[9, 11, 8, 5, 7, 12, 16, 14]

输出：11

## 思路

1. 暴力做法-$O(n^2)$
2. 调整迭代顺序（找最大值改为着最小值）本质：减元素会让之前找到的的最值失效；而加元素只需要拿新加的元素与前最值比较即可

## 最直观的思路-暴力做法

```cpp
class Solution {
public:
    int maxDiff(vector<int>& nums) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j>) {
                max_profit = max(max_profit, nums[j] - nums[i]);
            }
        }
        return max_profit;
    }
};
```

## 优化思路

你需要知道的两个前置技巧：
**双层定值拆分原则**：当涉及两层循环时，可以将外层循环变量当成定值，对循环的整体结构进行整体审视，确定是否可以优化掉一层。
**最值计算的累积效应**：当涉及最值计算时，减元素会让之前找到的的最值失效；而加元素只需要拿新加的元素与前最值比较即可

我们的优化，需要你知晓上面的两个技巧，然后做适当的**启发式思考**，具体过程我已经呈现在下面的注释中了。

```cpp
class Solution {
public:
    int maxDiff(vector<int>& nums) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < nums.size(); ++i) {
            //如果把i当作定值，那么下面的这层循环是在寻找num[j]的最大值
            //i每增加1,内层循环会减少一个元素，根据之前的启发式，减少元素会让之前计算的最大值失效，所以不得不重新计算最大值；
            //我们尝试着调整迭代顺序。
            for (int j = i + 1; j < nums.size(); ++j>) {
                max_profit = max(max_profit, nums[j] - nums[i]);
            }
        }
        return max_profit;
    }
};
```

那么，我们更换迭代顺序之后。

```cpp

class Solution {
public:
    int maxDiff(vector<int>& nums) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int i = 1; i < nums.size(); ++i) {
            //调整迭代顺序后，如果把i当作定值，那么下面的这层循环是在寻找num[j]的最小值
            //i每增加1,内层循环会增加一个元素，增加一个元素后，只需比较新的元素与之前的最小值；
            //便可以得到新的最小值，而不需要循环查找
            //nums[i]是每次的新元素
            min_price = min(min_price, nums[i]); 
            /*
            for (int j = 0; j < i - 1; ++j>) {
                max_profit = max(max_profit, nums[i] - nums[j]);
            }
            */
            max_profit = max(max_profit, nums[i] - min_price);
        }
        return max_profit;
    }
};
```

