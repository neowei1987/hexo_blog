---
title: 数据库必知必会-事务篇
date: 2022-02-16 23:20:03
updated:
mathjax: true
categories:
tags: 
- 数据库
---

##### 事务的特性

- A 原子性(Atomicity)，要么执行要么不执行
- C 一致性(Consistency)，事务将数据库从一种状态转变为下一种一致的状态。在事务开始之前和事务结束以后，数据库的完整性约束没有被破坏。（事务的acid不是完全正交的，尤其是一致性，可能跟原子性、隔离性都有一定关系。一致性是一个更宏观的要求。）
- I 隔离型(Isolation)，数据库允许多个并发事务同时对其数据进行读写和修改的能力，隔离性可以防止多个事务并发执行时由于交叉执行而导致数据的不一致。事务隔离分为不同级别，包括未提交读（Read uncommitted）、提交读（read committed）、可重复读（repeatable read）和串行化（Serializable
- D 持久性(Durability)，一旦事务提交，对数据的改变就是永久的，即便系统故障也不会丢失

#### 事务同时运行可能出现的问题

- 脏读，事务B读到事务A还没有提交的数据
- 不可重复读，一行被SELECT两次，返回的结果不一样
- 幻读，两次读取返回的集合不一样

##### 事务的四种隔离级别

- 读未提交，在该隔离级别，会出现脏读、不可重复读、幻读等问题。
- 读已提交，该隔离级别解决了脏读的问题，依旧会出现不可重复读、幻读问题。
- 可重复读，该隔离解决进一步解决了不可重复读的问题，会出现幻读问题。（但是对于InnoDB存储引擎，通过间隙锁解决了该问题，不会出现幻度现象）
- 串行，该隔离级别把所有操作都串行化了，没有并发访问，解决了以上所有问题。

![数据库各隔离级别会出现的问题](https://images.gitbook.cn/d9fd08e0-a1b6-11ea-bf38-950ba54cfedc)

![Mysql_InnoDB引擎各隔离级别会出现的问题](https://img-blog.csdnimg.cn/20210126002636194.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0OTA4ODM4,size_16,color_FFFFFF,t_70)

虽说希望你了解，但是友情提示一波：线上高并发应用，尽量**不要用事务**！
