---
title: 数组系列-分类汇总
date: 2021-01-11 22:25:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

数组，作为一种最简单的数据组织方式，在平常工作中用处非常广泛。

## 关于数组你一定要知道的

## 数组的常见技巧

- 自Hash

本质：把数组当作hash

给出的数组中每个元素的范围都是 [1, n]，并且要求的空间复杂度是$O(1)$

可以考虑：**原地修改数组**又叫**自Hash**，其本质上就是把数组当作hash

修改方法：取反，总之需要有办法来识别打了标记的元素

对元素打标记时，打的标记需尽量保存信息(对相反数取绝对值，就能够还原原始内容），不可影响问题的求解。

- 原地交换

还有另外一种技巧，我们称之为原地交换，其基本要求在于：

每一个元素都需要有对应的坑位，如果我们在他对应的坑位上的话，就进行swap；如此往复

1）检查某一个元素是否在他期望出现的位置上

2）如果在了，就啥也不做

3）如果不在，就与目标位置上的元素进行替换（替换之后，新的元素又不满足了，那我们就继续）

## 数组相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [缺失的第一个正数](firstMissingPositive.html)  |原地交换|
| | [数组中重复的数据](duplicateInArray.html)  |原地交换)|
| | [数组中重复的数据-无额外空间](duplicateInArrayNoSpace.html)  |二分查找|

## Pattern: Cyclic Sort 循环排序

参考：
https://blog.csdn.net/weixin_43989102/article/details/111397072