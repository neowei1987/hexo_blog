---
title: 找出次数一半的数
date: 2022-02-26 21:42:03
updated:
mathjax: true
categories:
- 数据结构与算法
- 剑指Offer
tags: 
- 摩尔投票法
---

输入n个整数，输出出现次数大于等于数组长度一半的数。
输入描述:

每个测试输入包含n个空格分割的n个整数，n不超过100，其中有一个整数出现次数大于等于n/2。
输出描述:

输出出现次数大于等于n/2的数。

#### 解题思路

摩尔投票法的核心就是一一抵消，删除不同的数。

因为要找过半的数，用一个变量count记录读取每个变量变化的次数，一个变量temp记录可能过半的数。

先让count = 1，然后让temp = vec[0]，然后往后遍历一遍。
碰到和temp相同的数就给count++，否则就count--，如果count变成0，就让temp=vec[i] (v数组遍历过程中的当前值),并让count = 1。

如此遍历一遍，因为有一个数过半，所以temp最后肯定存储的是过半的数

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

参考：
https://www.zhihu.com/question/284969980/answer/440979325