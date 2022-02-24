---
title: 双指针技巧
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 思想技巧
tags: 
- 二分
---

一类是「快慢指针」，另一类是「左右指针」

前者解决主要解决链表中的问题，比如典型的判定链表中是否包含环；后者主要解决数组（或者字符串）中的问题，比如二分查找。

双指针类 （数组A，2*n个元素，n个奇数、n个偶数，设计一个算法，使得数组奇数下标位置放置的都是奇数，偶数下标位置放置的都是偶数 两种思路：双指针、借助于栈）

盛水做多的容器

<!-- more -->

in place 的更新数组，需要一个index记录更新之后的数组，另一个index跑遍原来的数组； 

还有就是找到数组里面的N个数使得这几个数满足一定的条件（如几个数之和必须为某一个特定的数）；还有就是一类特殊的问题雨水储存问题

首先数组是否排序，根据信息论的看法或者能量守恒的原理，数组是否排序与墒有关，

墒的本质就是描述事物有序程度的度量，换句话说事物越有序墒的值越低，并且本质是墒会自然的会增大在无外力干扰的状况下，也就是事物总是向着无序发展的。

而怎样让事物变的有序呢，那么就需要外力能量的输入来使得墒变小或者变的有序。那么在数组是否有序的问题上，我们希望它是有序的，如果不是那么就需要花费“能量”让他的墒变小，

这样复杂度O(nlogn)就上去了，这里复杂度可以看作为外作用力的体现。

其次双指针问题的本质其实是由于有两个或者多个元素有相互作用或者相关联，因此在改变其中一个元素的同时其他几个元素也需要跟着改变，

因此双指针问题一般是在满足几个元素关系不变的情况之下，改变一个元素的同时，寻找其他几个元素满足现有的关系情况。

https://www.jianshu.com/p/b5f9ac6de184

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [最长无重复字串](../longestSubstringWithoutDuplication.html)  |滑动窗口、字符串类|


有字符串,将所有连续的ac跟单独的b去掉后的字符串：如acccccb->ccc; aacceacdb->ed
    时间复杂度O(n) 空间复杂度O(n) --> 时间复杂度O(n) 空间复杂度O(1)

    2. Pattern: two points, 双指针类型
经典题目：
Pair with Target Sum (easy)
Remove Duplicates (easy)
Squaring a Sorted Array (easy)
Triplet Sum to Zero (medium)
Triplet Sum Close to Target (medium)
Triplets with Smaller Sum (medium)
Subarrays with Product Less than a Target (medium)
Dutch National Flag Problem (medium)
≈