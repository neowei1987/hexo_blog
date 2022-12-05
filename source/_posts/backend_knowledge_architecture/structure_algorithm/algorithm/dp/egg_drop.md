---
title: 动态规划-扔鸡蛋问题
date: 2022-12-05 16:03:03
updated:
description: 
mathjax: true
categories:
tags: [动态规划]
---

## 0. The Two Egg Problem

You are given two eggs, and access to a 100-storey building. Both eggs are identical. The aim is to find out the highest floor from which an egg will not break when dropped out of a window from that floor. If an egg is dropped and does not break, it is undamaged and can be dropped again. However, once an egg is broken, that’s it for that egg.

If an egg breaks when dropped from floor n, then it would also have broken from any floor above that. If an egg survives a fall, then it will survive any fall shorter than that.

The question is: What strategy should you adopt to minimize the number egg drops it takes to find the solution?. (And what is the worst case for the number of drops it will take?)

<!-- more -->

## 1. 假如你只有一个鸡蛋

显然，你**不得不**从一层到100层，一层一层的扔，因为如果不按这种策略的话，万一层坏掉了，你就没有更多的鸡蛋了？

## 2. 假如你有无数的鸡蛋

如果你有无穷多的鸡蛋，我可以采用**二分策略**去扔，第一次50层，如果碎了，那就第二次25层；如果没有碎，那就75层（50 + 25）

## 3. 如果有2个鸡蛋呢？

假设最坏情况下（也就是最多）能扔N次； 我们的扔蛋策略如下：

第一次，在$N_{th}$层扔

如果碎了，那第1层到第N-1层，就从低到高依次扔（这种情况下次数为1 + (N - 1) = N，没有超过N，ok

如果没有碎，那么我就在$2N + 1$层扔（在第一次N的基础上，往上爬N-1层）为什么呢？爬的层数过多，总的次数会超过N次（与既定假设矛盾）；如果爬的层数过少，存在浪费现象，次数没有minimize。

所以，N + (N - 1) + (N - 2) + ... + 2 + 1 是我总的可以探测到的层数；

## 4. 普遍情况，如果有k个鸡蛋，有N层楼？

F[n,k]表示k个鸡蛋，扔n次能够reach的最大层数

D[n,k]表示k个鸡蛋，n层楼，需要扔的次数；

正难则反，对于D来说，可以通过动态规划来实现，但是要想求他的解析解比较困难。

但是对于F来说，我们可以借助一个G(n,k) = F() - F()来进行直接求解。

参考：
https://brilliant.org/wiki/egg-dropping/#a-better-approach
https://datagenetics.com/blog/july22012/index.html
https://spencermortensen.com/articles/egg-problem/