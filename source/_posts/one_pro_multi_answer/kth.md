---
title: 第k大元素|一题多解
date: 2021-1-2 15:47:03
mathjax: true
categories:
tags: 
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
* 线性选择（快排思想）
* 借助堆

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

