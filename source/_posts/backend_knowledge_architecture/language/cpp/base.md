---
title: cpp语言-内存模型
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
categories:
- 编程语言
tags: 
- cpp
---

virtual destructor()

将Base析构函数声明为virtual函数时，执行delete base ;语句就会删除subModel的对象；

exception

try catch 

![CPP内存模型](https://img-blog.csdnimg.cn/bf280dc2bc534d07a21a559aa6f643b6.png)


void *operator new (size_t size,void *pbuffer)

可以做某一个类的静态成员函数