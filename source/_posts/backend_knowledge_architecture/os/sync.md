锁的实现：
单核：test and set
多核：锁总线的状态下，test  and set

参考：

http://jm.taobao.org/2011/12/07/1347/

https://blog.csdn.net/heiyeshuwu/article/details/9722443

https://www.cnblogs.com/jing99/p/11984966.html

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