---
title: java语言-线程同步
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
### volatile

volatile 的三点：
（1）保证可见性（ 主内存 VS JAVA内存）
（2）禁止指令重排

Instance = new Singleton();可以分为以下三步：
Memory = allocate();//1.分配对象内存空间
Instance(memory)//2.初始化对象
Instance = memeory //3.设置初始化的对象指向刚分配的内存地址，此时instacne ! =null

步骤2和步骤3不存在数据依赖关系，所以这种重排序是允许的

Memory = allocate();
Instance = memeory
Instance(memory)//2.初始化对象

所以这个时候出现的问题为多个线程在这里获得单例对象，第一个访问者在instance = new Singleton();这一步骤时由于指令重排序，底层先给对象分配好了地址，此时不为空，这个时候其他线程访问，instacne不为空，但是得不到实例对象。

（3）不保证原子性

volatile的应用场景

DCL（Double Check Lock双端检索机制）

双端检索机制不一定安全，原因是有指令重排序的存在，加入volatile可以禁止指令重排。 在某一个线程执行到第一次检测时，此时instance不为null，但是insatnce的引用对象可能没有初始化完成

如何保证原子性

 这种问题可以使用synchronized 或者使用原子变量 来解决。原子变量通过调用unsafe类的cas方法实现了原子操作，由于CAS是一种系统原语,原语属于操作系统用于范畴,是由若干条指令组成,用于完成某个功能的一个过程,并且原语的执行必须是连续的,在执行过程中不允许中断,也即是说CAS是一条原子指令,不会造成所谓的数据不一致的问题。

### synchronized 的锁升级过程

无锁-》偏向锁-》轻量级CAS自旋锁-》重量级锁

总体原理就是通过存储最新访问变量的Thread-id来做判定，如果是同一个则无锁；通过简单的CAS自旋锁来判断是否需要block访问；只有需要block访问才启动重量级锁。

https://blog.csdn.net/weixin_45606067/article/details/126766885

### synchronized 与 lock的区别

区别如下：

1.Lock是显示锁（手动开启和关闭锁）, synchronized时隐式锁，出来作用域自动释放

2.Lock只有代码块锁，synchronized有代码块锁和方法锁

3.使用Lock锁，JVM将花费较少的时间来调度线程，性能更好。并且具有更好的扩展性（提供了更多子类）

4.lock是一个接口，而synchronized是java的一个关键字，synchronized是内置的语言实现；

5.异常是否释放锁：
    synchronized在发生异常时候会自动释放占有的锁，因此不会出现死锁；而lock发生异常时候，不会主动释放占有的锁，必须手动unlock来释放锁，可能引起死锁的发生。（所以最好将同步代码块用try catch包起来，finally中写入unlock，避免死锁的发生。）

6.是否响应中断
    lock等待锁过程中可以用interrupt来中断等待，而synchronized只能等待锁的释放，不能响应中断；

7.是否知道获取锁
    Lock可以通过trylock来知道有没有获取锁，而synchronized不能；

8.Lock可以提高多个线程进行读操作的效率。（可以通过readwritelock实现读写分离）

9.在性能上来说，如果竞争资源不激烈，两者的性能是差不多的，而当竞争资源非常激烈时（即有大量线程同时竞争），此时Lock的性能要远远优于synchronized。所以说，在具体使用时要根据适当情况选择。

10.synchronized使用Object对象本身的wait 、notify、notifyAll调度机制，而Lock可以使用Condition进行线程之间的调度

AQS

condtion是通过Reentlock的newCondtion方法创建出来的

rwlock也是基于AQS实现的读写锁

Semaphore 是一套单独的机制，用来实现信号量，多个线程共同访问一个资源。
