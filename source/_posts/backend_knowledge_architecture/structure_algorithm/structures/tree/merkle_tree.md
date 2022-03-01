---
title:  MerkleTree - 概览
date: 2022-03-01 13:41:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

Merkle Tree，通常也被称作Hash Tree，顾名思义，就是存储hash值的一棵树。Merkle树的叶子是数据块(例如，文件或者文件的集合)的hash值。非叶节点是其对应子节点串联字符串的hash。

![Merkle Tree](https://images2015.cnblogs.com/blog/834896/201605/834896-20160527163537178-321412097.png)