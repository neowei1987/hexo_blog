---
title: 数据库必知必会-InnoDB存储引擎
date: 2022-02-16 23:20:03
updated:
mathjax: true
categories:
tags: 
---


我们通过几个问题来介绍InnoDB存储引擎

1. LBCC  VS MVCC

Lock Based Concurrency Control（LBCC）

保证前后两次读取数据一致，那么我读取数据的时候，锁定我要操作的数据，不允许其他的事务修改就行了。如果仅仅是基于锁来实现事务隔离，一个事务读取的时候不允许其他时候修改，那就意味着不支持并发的读写操作，而我们的大多数应用都是读多写少的，这样会极大地影响操作数据的效率。

MVCC Multi Version Concurrency Control（MVCC)

MVCC是InnoDB存储引擎为了实现事务的隔离级别而引入的一种乐观锁机制。
如果要让一个事务前后两次读取的数据保持一致，那么我们可以在修改数据的时候给它建立一个备份或者叫快照，后面再来读取这个快照就行了。

MVCC 的核心思想是： 我可以查到在我这个事务开始之前已经存在的数据，即使它在后面被修改或者删除了。在我这个事务之后新增的数据，我是查不到的。

Undo log: 是什么？ 通过它解决了什么问题？ 数据的多个版本，临时写在undo log中，并通过链表管理起来。

InnoDB为数据库中的每一行添加了三个隐藏字段：DB_TRX_ID(事务版本号)、DB_ROLL_PTR(回滚指针)、DB_ROW_ID(隐藏ID)。

- DB_TRX_ID：记录了创建/更新这条数据的事务版本号（版本号会递增）。
- DB_ROLL_PTR：记录了一个指向undo log中历史版本的数据指针。（用来支持回滚操作）
- DB_ROW_ID：一个自增的隐藏行ID。

InnoDB基于事务版本号、回滚指针这两个字段，可以在undo log中形成一个单向链表，最新版本的数据放在链表头部，历史数据通过DB_ROLL_PTR指针进行关联。如下图所示

![undo list](https://pic1.zhimg.com/80/v2-85a123161b23631a22e89313e76caa2c_1440w.jpg)

一致性读视图包括：视图数组（活跃的事务） + 高水位（已经创建过的事务ID + 1）

InnoDB在事务开启后执行第一个查询时，会创建一个快照（下文称之为ReadView），这个ReadView包含了以下信息

- m_ids: 活动事务id列表（活动事务指的是已经开始、尚未提交/回滚的事务）
- min_trx_id: 最小活动事务id
- max_trx_id:最大活动事务id
- creator_trx_id:当前事务id

紧接着InnoDB会通过查询语句定位到最新版本的数据行，并根据以下规则获取到可以访问的数据版本。

- 如果被访问版本的trx_id，与readview中的creator_trx_id值相同，表明当前事务在访问自己修改过的记录，直接返回该版本的数据；
- 如果被访问版本的trx_id，小于readview中的min_trx_id值，表明生成该版本的事务在当前事务生成readview前已经提交，直接返回该版本的数据；
- 如果被访问版本的trx_id，大于或等于readview中的max_trx_id值，表明生成该版本的事务在当前事务生成readview后才开启，此时该版本不可以被当前事务访问，需要通过隐藏的回滚指针从undo log中读取历史版本；
- 如果被访问版本的trx_id，在readview的min_trx_id和max_trx_id之间，则需要判断trx_id值是否在m_ids列表中？
(1)如果在：说明readview创建时，创建该版本数据的事务还未提交，因此需要通过回滚指针读取历史版本并返回。
(2)如果不在：说明readview创建时，创建该版本数据的事务已经提交，所以直接返回该版本的数据；

1. InnoDB是如何解决脏读问题的？

如果是读已提交，那么事务每一个语句执行前都会重新计算出新的视图。 也就解决了脏读问题。

2. InnoDB是如何解决不可重复读问题的？

如果是可重复读，那么事务开启时创建一次访问视图。同一个事务中后续所有的查询共用一个ReadView，由此便解决了不可重复读的问题。

3. InnoDB是如何解决幻读问题的？

快照读、锁定读：了解这两种读取方式的发生时机以及如何实现的？

快照读是指通过MVCC实现的非阻塞读，常见的快照读操作如下：

select xxx from xxx

当前读也叫加锁读，每次读取数据都是读取数据的最新版本，并且会对其进行加锁。常见的当前读操作如下

- select xxx from xxx lock in share mode (共享锁/读锁)
- select xxx from xxx for update （排它锁/写锁）
- update 、delete、insert

为什么要区分这两种读操作呢？因为MVCC并不能解决幻读的问题。即使是在可重复读级别，通过当前读依然会出现幻读问题。

此问题最终是通过间隙锁（next-key lock)来解决的。

4. InnoDB是如何解决事务的一致性问题的？

Redo log: 是什么？ 通过它解决了什么问题？

redo log是InnoDB存储引擎为了解决事务持久性而引入的WAL技术。借助redo log，InnoDB存储引擎将事务的commit提交简化为一次内存操作与一次磁盘写入操作。如果磁盘页中的数据发生了丢失，也就是在崩溃恢复过程中，存储引擎会通过重做redo log中的操作来进行数据恢复。

binlog: 又是什么？他是干什么用的？ 了解主从同步原理。

binlog是Mysql server层为了解决主从数据同步而引入的一套日志系统。binlog中记录的是一个数据行发生了什么操作。

Redo Log与binlog的两阶段提交

- prepare阶段，先写入rede log（状态为准备中）
- 写入binlog（状态为已提交）--- TX_ID
- commit阶段，写入redo log（状态为已提交）

5. InnoDB的几个关键特性：insert buffer、double write、自适应hash索引、异步写等
