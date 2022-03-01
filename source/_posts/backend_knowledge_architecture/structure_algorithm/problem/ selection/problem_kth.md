---
title: 第k大元素
date: 2021-1-2 15:47:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 线性选择
- 一题多解
---

输入n个整数，找出其中最小的k个数。

注意：

数据保证k一定小于等于输入数组的长度;
输出数组内元素请按从小到大顺序排序;
样例
输入：[1,2,3,4,5,6,7,8] , k=4

输出：[1,2,3,4]

常见解法：

* 排序
* 借助堆: 借助大小为K的堆，从而实现快速比较。
* 线性选择（快排思想） --普通：最坏的时间复杂度$O(lgn)$
* 线性选择（快排思想） --基于中位数的select升级：借助基于中位数的select算法来选择枢点，可以尽可能的2分问题，从而使得最坏的时间复杂度控制在$O(n)$

```cpp
class Solution {
public:
    vector<int> getLeastNumbers_Solution(vector<int> input, int k) {
        priority_queue<int, vector<int>, less<int>> q; //大顶堆
        
        for (int i = 0; i < input.size(); ++i) {
            if (q.size() < k) {
                q.push(input[i]);
            }
            else {
                if (input[i] < q.top()) {
                    q.pop();
                    q.push(input[i]);
                }
            }
        }
        
        vector<int> res;
        
        while (q.size()) {
            res.push_back(q.top());
            q.pop();
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
```
