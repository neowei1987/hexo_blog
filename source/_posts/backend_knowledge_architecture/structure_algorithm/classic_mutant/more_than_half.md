---
title: 数组中超过一半的数字
date: 2021-1-2 15:50:03
mathjax: true
categories:
tags: 
---

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

假设数组非空，并且一定存在满足条件的数字。

思考题：

假设要求只能使用 O(n) 的时间和额外 O(1) 的空间，该怎么做呢？
样例
输入：[1,2,1,1,3]

输出：1

摩尔投票法的核心就是一一抵消，删除不同的数。

https://www.zhihu.com/question/284969980/answer/440979325

```cpp
class Solution {
public:
    int moreThanHalfNum_Solution(vector<int>& nums) {
        int cnt = 0;
        int val = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (!cnt) {val = nums[i];}
            
            if (nums[i] == val) {
                cnt++;
            }
            else {
                cnt--;
            }
        }
        
        return val;
    }
};
```

