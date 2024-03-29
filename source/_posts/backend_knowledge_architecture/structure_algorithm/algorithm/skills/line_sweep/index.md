---
title: 扫描线
date: 2020-12-29 23:34:03
mathjax: true
categories:
- 数据结构与算法
tags: 
---

扫描线是一条想象中的向右扫过平面的竖直线。也因此，以此思想为基础的算法也被称为平面扫描算法(Plane Sweep Algorithm)，我们以某些事件为基础扫描我们思考的问题以使扫描离散化。

这些事件都是以我们思考的问题为基础，我们将在下面讨论的算法中看见。除去这些事件以外，我们需要维护一些数据结构来储存以y坐标为顺序排列的点（这一顺序有时可能会改变）以助益于在扫描到某些事件时进行操作。在一些情况，该数据结构只储存活动事件。

另一个需要注意的事情是，这种算法的效率取决于我们选用的数据结构。一般地，我们可以用C++中的set，但有时可能我们需要储存更多东西，所以我们可能采用平衡二叉树。
