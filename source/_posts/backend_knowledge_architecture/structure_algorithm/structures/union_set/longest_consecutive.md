---
title:  并查集系列之最长连续序列
date: 2022-03-01 16:13:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

Longest Consecutive Sequence 求最长连续序列, $O(n)$复杂度

解题思路：

  1. hash来记录是否使用过，以某个元素为中心，向两侧扩展
  2. 带size的并查集
  
```c++
class Solution {
public:
    unordered_map<int,int> father_map;//节点-父节点
    unordered_map<int,int> child_count;// 节点-子节点个数
    int longestConsecutive(vector<int>& nums) {
        int res = 1;
        if( nums.size() == 0) return 0;
        for(int i = 0;i < nums.size();i++)
        {
            father_map[nums[i]] = nums[i];
            child_count[nums[i]] = 1;
        }
        for(int i = 0;i < nums.size();i++)
        {
             if( father_map.find(nums[i]+1) != father_map.end())
             {
                 res = max (res,mergexy(nums[i],nums[i]+1));
             }
        }
        return res;
    }
    int getfather(int i)
    {
        if( father_map[i] == i)
        {
            return i;
        }
        else
        {
            father_map[i] = getfather(father_map[i]);
            return father_map[i] ;
        }
    }
    int mergexy(int x,int y)
    {
        x = getfather(x);
        y = getfather(y);
        if( x == y )
        {
            return child_count[x];
        }
        else
        {
            father_map[y] = x; 
            child_count[x] +=child_count[y];
            return child_count[x];
        }
    }
};
```