---
title:  并查集
date: 2022-03-01 13:58:03
mathjax: true
categories:
tags: 
---


并查集是一个代码很简单、但技巧性极强的数据结构，我们需要知道并查集的最重要特性：

能够在近乎$O(1)$的时间复杂度内完成元素归属集合以及元素合并的操作。

通常我们利用数组来实现并查集，并经常会通过路径压缩技巧来进行性能优化。

我们在图的连通性判定、最小生成树-kraskal等问题中可以看到常规并查集的应用。另外，我们有时候需要额外维护size、distance等额外属性去解决更多的问题。这种技巧也需要掌握。

#### 将多个集合合并成没有交集的集合

给定一个字符串的集合，格式如：{aaa， bbb，ccc}，{bbb，aaa,ddd}，{eeefff}，{ggg}，{dddhhh}要求将其中交集不为空的集合合并，要求合并完成后的集合之间无交集，例如上例应输出{aaabbbcccdddhhh}，{eeefff}，{ggg}。
（1）请描述你解决这个问题的思路；
（2）请给出主要的处理流程，算法，以及算法的复杂度
（3）请描述可能的改进。

回答：类似于并查集的思路

```cpp
并查集 —— 模板题 AcWing 836. 合并集合, AcWing 837. 连通块中点的数量
(1)朴素并查集：

int p[N]; //存储每个点的祖宗节点

// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ ) p[i] = i;

// 合并a和b所在的两个集合：
p[find(a)] = find(b);


(2)维护size的并查集：

int p[N], size[N];
//p[]存储每个点的祖宗节点, size[]只有祖宗节点的有意义，表示祖宗节点所在集合中的点的数量

// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ )
{
    p[i] = i;
    size[i] = 1;
}

// 合并a和b所在的两个集合：
size[find(b)] += size[find(a)];
p[find(a)] = find(b);


(3)维护到祖宗节点距离的并查集：

int p[N], d[N];
//p[]存储每个点的祖宗节点, d[x]存储x到p[x]的距离

// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x)
    {
        int u = find(p[x]);
        d[x] += d[p[x]];
        p[x] = u;
    }
    return p[x];
}

// 初始化，假定节点编号是1~n
for (int i = 1; i <= n; i ++ )
{
    p[i] = i;
    d[i] = 0;
}

// 合并a和b所在的两个集合：
p[find(a)] = find(b);
d[find(a)] = distance; // 根据具体问题，初始化find(a)的偏移量
```
