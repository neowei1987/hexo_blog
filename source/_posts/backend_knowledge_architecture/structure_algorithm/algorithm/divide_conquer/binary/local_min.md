---
title: 二分-局部最小
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
---

寻找数组局部最小值

解答思路：

只要有最小值，那我就可以找到。

a[0] <= a[1], 则a0就是极小值；
a[n - 2] >=  a[n - 1], 则a[n-1]就是极小值

否则，就如图(一定有最小值）：

![](https://img-blog.csdnimg.cn/a05469ef1d94408cbba43e2562274c07.png)
