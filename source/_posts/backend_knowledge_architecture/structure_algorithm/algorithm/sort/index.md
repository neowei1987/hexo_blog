---
title: 计算机排序算法
categories:
- 数据结构与算法
tags: 
- 排序
---

![总](https://img-blog.csdnimg.cn/20210316213527859.png)

outplace的都是稳定的；
outplace的需要一定的memory， inplace中的qsort由于是递归的，所有需要lgn的mem，其他的都不要额外的内存

inplace大多数都不稳定，除了冒泡排序、插入排序

|算法|思想|衍生问题|
|----|----|----|
|quick sort|分治思想，借助双指针在$O(n)$时间内完成partition|线性第k大，线性求中位数|
|merge sort|分治思想，双指针（稳定的）|逆序数|
|heap sort|借助容器来实现排序，还有类似的BST中序遍历|topK问题|
|counting sort|空间换时间，非比较；通过扫描min/max来支持负数，通过**累加和+倒序遍历来保持稳定**||
|bucket sort|抽屉原理，稳定排序，适合元素值集合较小的情况，特别适合外部排序|排序后最大间隔问题、大整数文件取中位数问题|
|radix sort|稳定子排序算法（计数排序、桶排序来实现）对数字进行k遍排序||
|shell sort|分块思想，缩小增量排序，一种特殊的插入排序；递减序列的选择很重要|适用于基本有序序列|
|insertion sort|减治思想，扑克牌|适用于基本有序序列
|Bubble sort|稳定|




