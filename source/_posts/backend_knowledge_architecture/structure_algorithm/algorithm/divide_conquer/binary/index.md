---
title: 二分系列-概览
date: 2022-02-25 22:47:03
updated:
copyright: true
password:
keywords: 
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 二分
---

### 关于二分

二分是分治的一种；问题收敛速度最快的一种。

通过每次把问题搜索空间排除一半，进而得到lgN的时间复杂度。

将区间分为两部分，第一部分满足某一个特征；第二部分满足另一个特征

通过二分来解决的问题包括：

1. 二分查找一个数组
2. 通过二分的方式，遍历所有可能的结果。然后判定结果是否ok。也就是把查找问题转换为判定问题。

二分答案：答案具有“单调性”，外层花费$logN$的时间转化为判定性问题.

答案具有“单调性”：注意是先0后1函数，还是先1后0函数，和二分的实现形式，是一直保持小于，还是能累加就累加？

一般定义判定是“是否存在一个小于等于、是否存在一个大于等于”，这么定义是显然有单调性的

二分出的答案一般对check的进行有所帮助

```cpp
//整数二分算法模板 https://www.cnblogs.com/smallocean/p/11913963.html

bool check(int x) {return true;/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;    // check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

//浮点数二分算法模板 —— 模板题 AcWing 790. 数的三次方根
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double bsearch_3(double l, double r)
{
    const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return l;
}
```

## 二分相关题目索引

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
|| [查第一个出现的位置](getNumberOfK.html)  ||
|| [递增找number与index相等](getNumberSameAsIndex.html)  ||
|| [重复数字出现次数](moving_cnt.html)  ||
|| [旋转数组找最值](find_min_in_rotated_array.html)  ||
|| 求两个有序数组前K大的数|考虑A的中间元素m/2和B的中间元素n/2||
|| 多路归并| 求m个有序数组前K大的数 | 维护一个大小为m的堆||

参考：

https://zhuanlan.zhihu.com/p/157779732

https://www.dazhuanlan.com/2019/12/16/5df6e82127d88/

https://blog.csdn.net/weixin_34355715/article/details/94465888

https://blog.csdn.net/weixin_43626741/article/details/104364387
