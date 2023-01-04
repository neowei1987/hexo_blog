---
title: java语言-reflect
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
categories:
- 编程语言
tags: 
- java
---

https://cloud.tencent.com/developer/article/1856972

优点：

1.能够运行时动态地获取类的实例，提高灵活性

2.与动态编译结合

缺点：
1）使用反射性能较低，需要解析字节码，将内存中的对象进行解析。

解决方案：

1、通过setAccessible(true)关闭JDK的安全检查来提升反射速度；

2、多次创建一个类的实例时，有缓存会快很多

3、ReflflectASM工具类，通过字节码生成的方式加快反射速度

2）相对不安全，破坏了封装性（因为通过反射可以获得私有方法和属性）
