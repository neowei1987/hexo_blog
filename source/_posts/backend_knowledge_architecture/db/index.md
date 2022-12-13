---
title: 数据库必知必会
date: 2022-02-16 23:20:03
mathjax: true
categories: 
tags: 
- 数据库
---

1、一张表，里面有 ID 自增主键，当 insert 了 17 条记录之后，删除了第 15,16,17 条记录，再把 Mysql 重启，再 insert 一条记录，这条记录的 ID 是 18 还是 15 ？

(1) 如果表的类型是 MyISAM，那么是 18

因为 MyISAM 表会把自增主键的最大 ID 记录到数据文件里，重启 MySQL 自增主键的最大ID 也不会丢失

（2）如果表的类型是 InnoDB，那么是 15

InnoDB 表只是把自增主键的最大 ID 记录到内存中，所以重启数据库或者是对表进OPTIMIZE 操作，都会导致最大 ID 丢失
