---
title: 概率相关问题
date: 2021-03-21 23:34:03
---

给定一个函数rand()能产生1到m之间的等概率随机数，产生1到n之间等概率的随机数？
https://www.cnblogs.com/double-win/archive/2014/04/07/3650314.html
https://my.oschina.net/u/4401597/blog/4038277

```cpp
int rand10()
{
int x;
do
{
    x = (rand7()-1)*7+rand7();
}while(x > 40)
return (x-1)%4+1;
}
```

有一个随机生成器randA()，以p的概率返回0，1-p的概率返回1，利用这个randA()构造randB()，使randB()等概率的返回0和1，即0.5的概率返回0，0.5的概率返回1。

```cpp
int randB()
{
int x1, x2;
do
{
    x1 = randA();
    x2 = randA();
}while(x1+x2 != 1)
return x1;
}
```

程序的输入包含两个整数m和n，其中$m \lt n $。输出是0~n-1范围内m个随机整数的有序列表，不允许重复。从概率的角度来说，我们希望得到没有重复的选择，其中每个选择出现的概率相等。

```cpp
void generate(int m,int n)
{
int t = m;
for(int i = 0; i < n; i++)
    if(Rand(0,n-1-i) < t) //即以t/(n-i)的概率执行下面的语句
    {
    printf("%d\n",i);
    t--;
    }
}
```

如何数据流中随机选出N个元素-蓄水池采样算法，具体步骤如下：
（1）先把N个坑位填上
（2）对于后面新来的第i元素，做如下概率处理：令X=rand(0, i)
A. 如果X在[0, m]之间，则用swap(X, i)
B. 否则啥也不做
深入一下，分布式蓄水池算法： https://www.jianshu.com/p/7a9ea6ece2af