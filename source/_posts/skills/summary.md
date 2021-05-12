---
title: 计算机思想汇总
date: 2020-12-30 13:34:03
mathjax: true
categories:
- 思想技巧
tags: 
- 二分
---

http://jm.taobao.org/2011/12/07/1347/

https://blog.csdn.net/heiyeshuwu/article/details/9722443

https://www.cnblogs.com/jing99/p/11984966.html

https://www.cnblogs.com/yeahwell/p/multiple-thinking-model.html
供原子性和持久性（ACID属性中的两个）的一系列技术。

    Source URL: http://zh.wikipedia.org/wiki/%E9%A2%84%E5%86%99%E5%BC%8F%E6%97%A5%E5%BF%97
在计算机科学中，预写式日志（Write-ahead logging，缩写 WAL）是关系数据库系统中用于提供原子性和持久性（ACID属性中的两个）的一系列技术。在使用WAL的系统中，所有的修改在提交之前都要先写入log文件中。
log文件中通常包括redo和undo信息。这样做的目的可以通过一个例子来说明。假设一个程序在执行某些操作的过程中机器掉电了。在重新启动时，程序可能需要知道当时执行的操作是成功了还是部分成功或者是失败了。如果使用了WAL，程序就可以检查log文件，并对突然掉电时计划执行的操作内容跟实际上执行的操作内容进行比较。在这个比较的基础上，程序就可以决定是撤销已做的操作还是继续完成已做的操作，或者是保持原样。
WAL允许用in-place方式更新数据库。另一种用来实现原子更新的方法是shadow paging，它并不是in-place方式。用in-place方式做更新的主要优点是减少索引和块列表的修改。ARIES是WAL系列技术常用的算法。在文件系统中，WAL通常称为journaling。PostgreSQL也是用WAL来提供point-in-time恢复和数据库复制特性。
操作系统的智慧

<!-- more -->

操作系统的智慧

CPU,RAM速度不匹配，基于局部性原理，引入硬件高速缓存内存

高速缓存的写策略：通写（write-through），写回（write-back）；读策略：预取

转换后援缓冲区 TLB：将线性地址映射为物理地址，加速线性地址转换

分页模型：多级索引


高速缓存命中率达到最优化：
一个数据结构中最常使用的字段放在该数据结构内的低偏移部分

lazy tlb
延迟更新TLB


pid分配管理：bitmap pidmap_array

thread 与 thread_info 紧密挨着；根据esp 屏蔽 低13位 可以最快的获取thread_info;
同时进程描述符指针在thread_info中的偏移为0!

也就是将： OS将task_struct指针存放到了栈上（可以通过esp做简单的AND操作即可）

list_head 双向链表
hlist_head hlist_node 散列表拉链

提高调度程序运行速度：建立多个可运行程序链表

根据PID定位task：PID哈希表

等待队列（双向链表）：
用自旋锁加保护的等待队列头
 等待队列链表的元素
等待队列中睡眠进程的唤醒：互斥进程，非互斥进程

进程切换

中断 IDT

每CPU变量：不需要同步的内核
数组，为每个cpu分配数组一元素
对不同CPU的并发访问提供保护，但是来自异步函数、内核抢占的访问不提供保护

原子操作
优化屏障、内存屏障

自旋锁、读写自旋锁

顺序锁（写者有较高优先级，当读者前后读到数据不一致时，重复读取）
系统相关的数据结构有使用！

RCU(读取-拷贝-更新)：只保护被动态分配并通过指针引用的数据结构
何时释放旧副本？ CPU经过静止状态后，定期检测！！

信号量

共享数据结构是一个单独的整数值，atomic_t
元素插入共享链表，涉及了两个指针赋值，写内存屏障可以避免看到坏的链表
获得自旋锁，必然禁止本地中断，本地软中断，自动禁止内核抢占

引用计数器（资源并发访问与释放而产生的竞争条件）

jiffies:子系统启动的节拍总数
顺序锁保护用于标志时钟中断数目64位计数器

软定时器
动态定时器的链表组（将同一时间段内即将到时的定时器归入一组）

NUMA
链表维护节点；节点包括管理区【硬件限制，ZONE_DMA, ZONE_NORMAL, ZONE_HIGHMEM】+page数组

pg_data_t
zone_t
page

将page到zone_t, pg_data_t的链接，以索引的形式存放到了page flag高位


动态内存分配与释放：管理区分配器 + 【伙伴系统 + 每CPU页框高速缓存】 * N


进程与线程

进程地址空间


进程与线程的联系与区别：
区别：进程切换与线程切换的一个最主要区别就在于进程切换涉及到虚拟地址空间的切换而线程切换则不会

锁的实现：
单核：test and set
多核：锁总线的状态下，test  and set

MESI 缓存一致性协议
Modified
Exclusive 
Shared
Invalid

https://www.qbitai.com/2019/12/9895.html
https://www.jianshu.com/p/d585b3938dea
https://www.jianshu.com/p/d585b3938dea

TODO 精读该系列文章
https://blog.csdn.net/ITer_ZC/article/details/40392787

CacheLine
所以我们处理线程安全可以有几个层次：
1. 能否做成无状态的不变对象。无状态是最安全的。
2. 能否线程封闭   
   （ 1）栈封闭，多采用局部变量 （2）线程局部存储（用空间换性能）（3）程序控制线程封闭（Hash，将同一hash val的的请求丢给同一个线程去处理）
3. 采用何种同步技术

并发/线程的一些概念，概念很重要，没有理论指导的话会导致理解不够全面
多线程问题的本质 -- 有序性，可见性，原子性
synchronize的底层实现
volatile的底层实现
无锁算法的底层实现 -- CAS
原子变量的实现
final关键字的新含义
深入理解Java内存模型
指令重排序和内存屏障
顺序一致性和Happens-before规则
一些基本的硬件知识
一些处理同步问题的技术

一个基本的CPU执行计算的过程如下：
1. 程序以及数据被加载到主内存
2. 指令和数据被加载到CPU的高速缓存
3. CPU执行指令，把结果写到高速缓存
4. 高速缓存中的数据写回主内存




数据库事务
ACID
脏读
幻读
不可重复度

并发控制：乐观并发控制、悲观并发控制
悲观锁(Pessimistic Lock)
每次操作之前都枷锁
悲观锁(Pessimistic Lock)
每次操作之前都枷锁

分层
具体应用：
1. 操作系统：硬件 --> 操作系统--> 应用程序--> 应用程序的通信、调用
2. 计算机网络：ISO七层
3. MVC：Model层--> View层--> Control层

Trade-Off
说明：没有对错、只有是否适合场景

懒人哲学：越简单、越傻瓜、用户使用的学习成本越低越好

让困于人：当我们遇到困难时，搞不定的或者我们自己搞成本很大的，交给别人来搞(一般让操作系统来搞，其实操作系统也是别人完成的软件系统)
留有余地: 可扩展性，让系统有可扩展性
足够智能：一个系统最好能解决所有的问题，跟人的感觉是一个万能的解决方案，也就是操作系统的魔术师的角色
时空转换：在一个纬度遇到的瓶颈，那就改变方案把瓶颈移到另外一个纬度 【内存页表太大，占用内存资源；那就页表分级，不活跃的放到磁盘】
策机分离和权利分离：一个系统或者平台在主要指定规则、提供通用化的插件即可
简单与美：苛求于简，归于永恒
数据冗余

正交：各个概念之间可以独立变化


数据分块

程序控制线程封闭设计

机架感知

预加载

COPY ON WRITE

Map Reduce 将数据用KV对来表示


全方位组相联
CPU cache
Kafka多分区多消费组
https://blog.csdn.net/dog250/article/details/79588437

索引思想
稠密索引
稀疏索引
多重表
倒排索引

spring设计思想


OS内存页表
路由表

二分

分治

局部性原理

池

懒加载

缓冲

双Buffer

顺序读写性能远大于随机读写性能

WAL

CheckPoint

Redo/Undo

Bitmap

MVCC

一致性Hash

多态

设计模式

IoC依赖反转
