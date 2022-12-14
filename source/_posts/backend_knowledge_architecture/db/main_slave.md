---
title: Mysql系列-主从同步
date: 2022-12-14 13:03:03
updated:
description: 
mathjax: true
categories:
tags: [数据库]
---

## 0. 主从复制机制

binlog

<!-- more -->

## 1. 主从延迟原因

主库和备库在执行同一个事务的时候出现时间差的问题，主要原因有：

有些部署条件下，备库所在机器的性能要比主库性能差。
备库的压力较大。
大事务，一个主库上语句执行10分钟，那么这个事务可能会导致从库延迟10分钟。

## 2. 如何降低主从延迟

因为单线程复制的能力全面低于多线程复制，对于更新压力较大的主库，备库可能是一直追不上主库的，带来的现象就是备库上seconds_behind_master值越来越大。
在实际应用中，建议使用可靠性优先策略，减少主备延迟，提升系统可用性，尽量减少大事务操作，把大事务拆分小事务。

## 3. 业务层面，如何处理过期读的方案

强制走主库方案；
sleep方案；
判断主备无延迟方案；
配合semi-sync方案；
等主库位点方案；
等GTID方案。

### binlog的三种格式

binlog 有三种格式：

Statement（Statement-Based Replication,SBR）：每一条会修改数据的 SQL 都会记录在 binlog 中。
Row（Row-Based Replication,RBR）：不记录 SQL 语句上下文信息，仅保存哪条记录被修改。
Mixed（Mixed-Based Replication,MBR）：Statement 和 Row 的混合体。

2.1.1 Statement
Statement 模式只记录执行的 SQL，不需要记录每一行数据的变化，因此极大的减少了 binlog 的日志量，避免了大量的 IO 操作，提升了系统的性能。

但是，正是由于 Statement 模式只记录 SQL，而如果一些 SQL 中 包含了函数，那么可能会出现执行结果不一致的情况。比如说 uuid() 函数，每次执行的时候都会生成一个随机字符串，在 master 中记录了 uuid，当同步到 slave 之后，再次执行，就得到另外一个结果了。

所以使用 Statement 格式会出现一些数据一致性问题。

2.2.2 Row
从 MySQL5.1.5 版本开始，binlog 引入了 Row 格式，Row 格式不记录 SQL 语句上下文相关信息，仅仅只需要记录某一条记录被修改成什么样子了。

Row 格式的日志内容会非常清楚地记录下每一行数据修改的细节，这样就不会出现 Statement 中存在的那种数据无法被正常复制的情况。

不过 Row 格式也有一个很大的问题，那就是日志量太大了，特别是批量 update、整表 delete、alter 表等操作，由于要记录每一行数据的变化，此时会产生大量的日志，大量的日志也会带来 IO 性能问题。

2.2.3 Mixed
从 MySQL5.1.8 版开始，MySQL 又推出了 Mixed 格式，这种格式实际上就是 Statement 与 Row 的结合。

在 Mixed 模式下，系统会自动判断 该 用 Statement 还是 Row：一般的语句修改使用 Statement 格式保存 binlog；对于一些 Statement 无法准确完成主从复制的操作，则采用 Row 格式保存 binlog。

Mixed 模式中，MySQL 会根据执行的每一条具体的 SQL 语句来区别对待记录的日志格式，也就是在 Statement 和 Row 之间选择一种。