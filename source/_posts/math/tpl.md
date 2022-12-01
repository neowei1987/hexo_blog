---
title: 学习机器学习可能用到的数学
date: 2022-12-01 21:03:03
updated:
description: 
mathjax: true
categories:
tags: [机器学习]
---

## 0. 背景介绍，把人吸引过来

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.3k2ld3hyx4q0.jpg)

积分中值定理、微分中值定理

---

泰勒公式

出发点：

    用简单的熟悉的多项式来近似代替复杂的函数

    易计算函数值，导数与积分仍是多项式

    多项式由它的系数完全确定，其系数又由它在一点的函数值及其导数所确定。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.6xln7bk35440.jpg)

阶数

阶乘：削弱高阶项的作用，让他晚一些起作用！

<!-- more -->

---

拉格朗日乘子法

求极值，并且带条件

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.4d7j3hvxg760.jpg)

---

矩阵

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.7kf4o4g1ei80.jpg)

 矩阵不满足交换律 $$A*B \ne B*A$$

 ![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.7j26y9yr7r40.jpg)

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.7e70x8sfgq00.jpg)

矩阵的秩： 矩阵中最大不相关向量的个数

行秩 = 列秩

二维 在秩为1的矩阵的作用下，会转换为一条线。
二维，在秩为1的矩阵的作用下，还是保持为二维。

矩阵 做 旋转、拉伸

特征值 特征向量 特征空间
![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.35a3lqh63wu0.jpg)

一个矩阵有很多的特征向量，特征提取就是取$\lambda$更大的特征向量

SVD矩阵分解

100W X 10W 稀疏矩阵 = 100W X 10 的矩阵 * 10 X 10W的矩阵

基变换：旋转、伸缩坐标轴

特征值分解

$A = U*A*U^{-1}$

U 特征向量 
A 是对角阵，取最大的几个，他们就是代表。

限制： N*N方阵

$MN = MK*KK*KN$，其中K << N, 取10%的特征，占据的样本可能会超过99%（因为比较稀疏）

---

概率函数（概率质量函数）

$p(x) = Prob(X = x)$

概率分布，就是一个表格，表中罗列了随机变量X的所有取值以及其对应的概率。

概率密度函数

频率分布直方图，当分组越来越多，轮廓会变为一条曲线。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.3s3afpjzgmo0.jpg)

简单随机抽样，
抽取的样本满足两点：
（1）样本X1，2…Xn是相互独立的随机变量。
（2）样本X1，X2.Xn与总体X同分布。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.6mtlivhz1ys0.jpg)

概率表达了在给定参数日时X=的可能性；而似然表示的是在给定样本X=时，参数的可能性！

二维随机变量

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.zhvrg2wn4w0.jpg)

联合概率分布，2 * 2表格

二维随机变量(X,Y)的分布函数

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.6hf4qer5oxk0.jpg)

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.39zcy7gk03m0.jpg)

边缘概率分布
$F_X(x) = P(X \le x) $

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.qsgyvy3jf3k.jpg)

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.7d2k1suwjgw0.jpg)

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.fds0ah0bp6g.jpg)

中心极限定理

样本的平均值约等于总体的平均值。不管总体是什么分布，任意一个总体
的样本平均值都会围绕在总体的整体平均值周围，并且呈正态分布。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.3dnlhkacz3u0.jpg)

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.5o17vqnyt6g.jpg)

正态分布

二项式分布

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.3khgm3xf8l00.jpg)

做N次实验，成功概率是p， 则成功k次的概率服从以上分布。

泊松分布

泊松分布中使用了这些符号：
·$\lambda$是事件发生的速率；
·t是时间间隔的长度；
·X是该时间间隔内的事件数，其中，X称为泊松随机变量，X的概率分布称为泊松分布。
·令$\mu$表示长度为的间隔中的平均事件数。那么，$\mu=\lambda*t$。

例如说一个医院中，每个病人来看病都是随机并独立的概率，则该医院一天（或者其他特定时间段，一小时，一周等等）接纳的病人总数可以看做是一个服从poisson分布的随机变量。但是为什么可以这样处理呢？通俗定义：假定一个事件在一段时间内随机发生，且符合以下条件：
·（1）将该时间段无限分隔成若干个小的时间段，在这个接近于零的小时间段里，该事件发生一次的概率与这个极小时间段的长度成正比。
·（2）在每一个极小时间段内，该事件发生两次及以上的概率恒等于零。
·（3）该事件在不同的小时间段里，发生与否相互独立。
则该事件称为poisson process。这个第二定义就更加利于大家理解了，回到医院的例子之中，如果我们把一天分成24个小时，或者24x60分钟，或者24x3600
秒。时间分的越短，这个时间段里来病人的概率就越小（比如说医院在正午12点到正午12点又一毫秒之间来病人的概率是不是很接近于零？）。条件一符合。另
外如果我们把时间分的很细很细，是不是同时来两个病人（或者两个以上的病人）就是不可能的事件？即使两个病人同时来，也总有一个人先迈步子跨进医院大
门吧。条件二也符合。倒是条件三的要求比较苛刻。应用到实际例子中就是说病人们来医院的概率必须是相互独立的，如果不是，则不能看作是poisso分布。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.24ayqxutj8zk.jpg)

均匀分布 uniform distribution

卡方分布
正态分布随机变量Xi的平方和服从卡方分布，有一个自由度参数$\lambda$

## 1. 是什么，XXX的本质

## 2. 为什么：XXX的价值

## 3. 怎么办：XXX带给我们的方法论
