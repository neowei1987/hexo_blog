---
title: 字节版-多路归并
date: 2022-02-27 20:53:03
mathjax: true
categories:
tags: 
---

算法题2：给定k个数组，每个数组都是有序的，且每个数组最大值-最小值<1000，1 < k<1000，求所有数的中位数。

解答思路：

定义一个结构体 NumCount {
    int number;
    int cnt;
}

预处理所有数据，将原来的数据用NumCount nums[k][1000]来保存。

用一个大顶堆来维护K路的最小值。

时间复杂度：$O(1000 * k)$
