---
title: 树
date: 2022-03-1 13:18:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

### heap

### red-black

更加平衡，没有极端；

### avl

过于平衡，查询性能最好，但是维护成本过高；

### treap

### splay-tree

### 区间树

区间树是在平衡树基础上进行扩展得到的支持以区间为元素的动态集合的操作，其中每个节点的关键值是区间的左端点。

![区间树](https://bkimg.cdn.bcebos.com/pic/279759ee3d6d55fb5d3e06426c224f4a21a4ddde)

### 线段树

线段树是一种二叉搜索树，与区间树相似，它将一个区间划分成一些单元区间，每个单元区间对应线段树中的一个叶结点。 [1]
对于线段树中的每一个非叶子节点[a,b]，它的左儿子表示的区间为[a,(a+b)/2]，右儿子表示的区间为[(a+b)/2+1,b]。因此线段树是平衡二叉树，最后的子节点数目为N，即整个线段区间的长度。

对编号连续的一些点进行修改或者统计操作，修改和统计的复杂度都是$O(log2(n))$

参考：https://blog.csdn.net/zearot/article/details/48299459

用线段树解题，关键是要想清楚每个节点要存哪些信息（当然区间起终点，以及左右子节点指针是必须的），

以及这些信息如何高效更新，维护，查询。不要一更新就更新到叶子节点，那样更新效率最坏就可能变成O(n)的了。

先建树，然后插入数据，然后更新，查询

### 树状数组（binary indexed tree）

树状数组所能解决的典型问题就是存在一个长度为n的数组，我们如何高效进行如下操作：

- update(idx, delta)：将num加到位置idx的数字上。

- prefixSum(idx)：求从数组第一个位置到第idx（含idx）个位置所有数字的和。

- rangeSum(from_idx, to_idx)：求从数组第from_idx个位置到第to_idx个位置的所有数字的和