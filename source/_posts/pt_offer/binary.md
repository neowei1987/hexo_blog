---
title: 剑指offer-二分相关
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 剑指Offer
tags: 
- 二分
---

二分

将区间分为两部分，
第一部分满足某一个特征；第二部分满足另一个特征

https://blog.csdn.net/weixin_34355715/article/details/94465888

====

统计一个数字在排序数组中出现的次数。

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

输入一个升序的数组的一个旋转，输出旋转数组的最小元素。

例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

数组可能包含重复项。

注意：数组内所含元素非负，若数组大小为0，请返回-1。

TODO: 进一步理解二分判定

样例
输入：nums=[2,2,2,0,1]

输出：0

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        if (nums.empty()) return -1;
        int n = nums.size() - 1;
        //特判
        while (nums[0] == nums[n]) {n--;}
        //特判
        if (nums[0] <= nums[n]) {
            return nums[0];
        }
        
        //二分模版
        int l = 0, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[0] > nums[mid]) r = mid;
            else  l = mid + 1;
        }
        
        return nums[r];
    }
};
```

例如输入排序数组[1, 2, 3, 3, 3, 3, 4, 5]和数字3，由于3在这个数组中出现了4次，因此输出4。

样例
输入：[1, 2, 3, 3, 3, 3, 4, 5] ,  3

输出：4

```cpp
class Solution {
public:
    int getNumberOfK(vector<int>& nums , int k) {
    if (nums.empty())  return 0;
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (nums[mid] < k) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }
    if (nums[r] != k) return 0;
    int left = r;

    l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = l + r  + 1 >> 1;
        if (nums[mid] > k) {
            r = mid - 1;
        }
        else {
            l = mid;
        }
    }

    return r - left + 1;
}
};
```

假设一个单调递增的数组里的每个元素都是整数并且是唯一的。

请编程实现一个函数找出数组中任意一个数值等于其下标的元素。

例如，在数组[-3, -1, 1, 3, 5]中，数字3和它的下标相等。

样例
输入：[-3, -1, 1, 3, 5]

输出：3
注意:如果不存在，则返回-1。

```cpp
class Solution {
public:
    int getNumberSameAsIndex(vector<int>& nums) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= mid) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }

        if (nums[r] != r) {
            return -1;
        }
        else {
            return r;
        }
    }
};
```