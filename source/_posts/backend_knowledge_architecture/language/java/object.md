---
title: java语言-object
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

equals VS  == 

（1）对象类型不同(一个是object的成员方法，一个是操作符)

（2）比较的对象不同 一个是对象内容是否ok， 一个是引用或者地址是否ok

（3）执行速度不同

在每个类中，在重写equals方法的时侯，一定要重写hashcode方法。

根据Object规范，规范约定：

如果两个对象通过equals方法比较是相等的，那么它们的hashCode方法结果值也是相等的。

如果两个对象通过equals方法比较是不相等的，那么不要求它们的hashCode方法结果值是相等的。

当在一个应用程序执行过程中， 如果equals方法比较中没有修改任何信息，那么在同一个对象上重复调用hashCode方法时，它必须始终返回相同的值。但如果从一个应用程序到了另一个应用程序，两个应用程序汇中调用hashCode方法的返回值可以是不一致的。