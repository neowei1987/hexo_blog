---
title: 线性回归介绍
tags:
mathjax: true
---

数学公式输入：
https://blog.csdn.net/honorzoey/article/details/113407979

具体见：https://www.bilibili.com/video/BV1uM411r7Cv?p=4&vd_source=9a48b33279c3ad3689807d049311d0ee

$Y = \theta * X + \epsilon $

我们现在的目标是找到一组$\Theta$可以让它乘以X之后尽可能的匹配Y

$\epsilon$为误差，服从均值为0，方差为$\mu^2$的正态分布

预测值与真实值之间有误差

学习的关键在于：确定什么样的参数最符合于你的目标

我们的目标是什么？ 让误差项尽可能的小，接近于0

loss函数等于0

高斯分布

$p(\epsilon^{(i)}) = \frac{1}{\sqrt{2 \pi}\sigma} exp(-\frac{(\epsilon^{(i)} - \mu)^{2}}{2\sigma^2}))$

条件概率：$p(y|x;\theta) = $p(\epsilon^{(i)}) $ 也服从正态分布。

对于某一个样本，要找到一个theta， 跟x组合之后，成为真实值y的可能性最大

对于所有的样本呢？ 由于是独立的，所以要相乘。

概率是受theta控制的，第一个OK了，第二个ok了，所有的样本都赢了； 

接下来我再玩的时候，我100%的可能性能赢。

似然函数：什么样的参数跟我们的数据组合后恰好是真实值。

独立同分布的情况下，联合概率密度 = 边缘概率1 * 边缘概率2 * ...


梯度下降
