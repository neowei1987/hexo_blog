---
title: 逆序数计算系列
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 剑指Offer
tags: 
- 归并排序
- 逆序数
---

在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。

输入一个数组，求出这个数组中的逆序对的总数。

样例
输入：[1,2,3,4,5,6,0]

输出：6

```cpp
class Solution {
public:
    vector<int> nums;
    vector<int> cp;
    int cnt;

    void merge(int l, int m, int r) {
        int k = l;
        while (k <= r) {
            cp[k] = nums[k];
            k++;
        }

        int i = l;
        int j = m + 1;
        k = l;

        while (i <= m && j <= r) {
            if (cp[i] <= cp[j]) 
            {
                nums[k++] = cp[i++];
            }
            else {
                cnt += (m - i + 1);
                nums[k++] = cp[j++];
            }
        }

        while (i <= m) {
            nums[k++] = cp[i++];
        }
        while (j <= r) {
            nums[k++] = cp[j++];
        }
    }

    void dfs(int l, int r) {
        if (l == r) return;
        int mid = l + r >> 1;
        dfs(l, mid);
        dfs(mid + 1, r);
        merge(l, mid, r);
    }

    int inversePairs(vector<int>& _nums) {
        if (_nums.empty()) return 0;
        nums = _nums;
        cnt = 0;
        cp.resize(nums.size());
        dfs(0, nums.size() - 1);
        return cnt;
    }
};
```
