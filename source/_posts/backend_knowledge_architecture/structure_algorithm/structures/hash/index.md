---
title: 哈希系列-概览
date: 2021-01-11 22:25:03
updated:
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

### hash实现

开放定址法：适合数据量小，装载因子小的场景

拉链法：适合存储大对象、大数据量的散列表，更加灵活，有更多的优化策略

```cpp
一般哈希 —— 模板题 AcWing 840. 模拟散列表
(1) 拉链法
    int h[N], e[N], ne[N], idx;

    // 向哈希表中插入一个数
    void insert(int x)
    {
        int k = (x % N + N) % N;
        e[idx] = x;
        ne[idx] = h[k];
        h[k] = idx ++ ;
    }

    // 在哈希表中查询某个数是否存在
    bool find(int x)
    {
        int k = (x % N + N) % N;
        for (int i = h[k]; i != -1; i = ne[i])
            if (e[i] == x)
                return true;

        return false;
    }

(2) 开放寻址法
    int h[N];

    // 如果x在哈希表中，返回x的下标；如果x不在哈希表中，返回x应该插入的位置
    int find(int x)
    {
        int t = (x % N + N) % N;
        while (h[t] != null && h[t] != x)
        {
            t ++ ;
            if (t == N) t = 0;
        }
        return t;
    }
```

### hash使用场景

- RPC负载均衡
- 数据分片，分布式存储，例如一致性hash

#### 特殊hash

1. 自hash， 用数组自身作为hash的container；
2. 位图
3. 布隆过滤器，多hash
4. 地理坐标hash， geo hash，二维转一维。

### 相关题目

10亿url按照计数排序

思路：

hash统计次数，然后单机排序、或者多机器归并排序

找出字符数组中只出现三次，且最早出现完三次的字符（eg：aabcbba输出b）

思路：

hashmap

### 数据结构实现

Hashmap是用hash算法实现的，我们通过put一个key和value进行存储，用get（key）来获取，在传入key时，hashmap会根据key.hashCode（）计算出hash值存储到bucket里面，当发生hash值相同，也就是hash冲突时，会使用链表+红黑树存储相同的hash值的value，如果冲突少，就用链表，冲突多，就用红黑树

Hashmap扩容：

·HashMap 初始化大小是 16 ，扩容因子默认0.75（可以指定初始化大小，和扩容因子）
·存的对象*负载因子*0.75（默认）大于总量就要扩容，扩容是键值重新排布，重新对底层数组容量取余分布
·JDK1.8之前是数组+链表结构、JDK1.8及之后是数组+链表+红黑树
·HashMap集合可以存储null键和null值

### java数据结构对比

hashMap 数组 + 链表 （冲突链表过长时，转为红黑树）线程不安全 允许null\null  不可以有序遍历

hashTable 线程安全，通过synchronized 不允许null\null  不可以有序遍历

treeMap 红黑树 线程不安全 可以有序遍历

