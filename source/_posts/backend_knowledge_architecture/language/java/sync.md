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

synchronized 的锁升级过程：无锁-》偏向锁-》轻量级CAS自旋锁-》重量级锁
https://blog.csdn.net/weixin_45606067/article/details/126766885

