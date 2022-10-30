---
title: 高性能服务器设计-同步OR异步
date: 2022-02-18 10:01:03
mathjax: true
categories:
- 
tags: 
- 高性能服务器
---

#### 判断使用同步或异步

计算qps * latency(in seconds)【最大并发】，如果和cpu核数是同一数量级，就用同步，否则用异步。

eg. qps = 2000，latency = 10ms，计算结果 = 2000 \* 0.01s = 20
和常见的32核在同一个数量级，用同步。

eg. qps = 100, latency = 5s, 计算结果 = 100 \* 5s = 500。和核数不在同一个数量级，用异步。

eg. qps = 500, latency = 100ms，计算结果 = 500 \* 0.1s = 50。基本在同一个数量级，可用同步。如果未来延时继续增长，考虑异步。

这个公式计算的是同时进行的平均请求数（你可以尝试证明一下），和线程数，cpu核数是可比的。当这个值远大于cpu核数时，说明大部分操作并不耗费cpu，而是让大量线程阻塞着，使用异步可以明显节省线程资源（栈占用的内存）。当这个值小于或和cpu核数差不多时，异步能节省的线程资源就很有限了，这时候简单易懂的同步代码更重要。

#### 异步或bthread

有了bthread这个工具，用户甚至可以自己实现异步。以“半同步”为例，在brpc中用户有多种选择：

发起多个异步RPC后挨个Join，这个函数会阻塞直到RPC结束。（这儿是为了和bthread对比，实现中我们建议你使用ParallelChannel，而不是自己Join）
启动多个bthread各自执行同步RPC后挨个join bthreads。
哪种效率更高呢？显然是前者。后者不仅要付出创建bthread的代价，在RPC过程中bthread还被阻塞着，不能用于其他用途。

如果仅仅是为了并发RPC，别用bthread。

不过当你需要并行计算时，问题就不同了。使用bthread可以简单地构建树形的并行计算，充分利用多核资源。比如检索过程中有三个环节可以并行处理，你可以建立两个bthread运行两个环节，在原地运行剩下的环节，最后join那两个bthread。过程大致如下：

```cpp
bool search() {
  ...
  bthread th1, th2;
  if (bthread_start_background(&th1, NULL, part1, part1_args) != 0) {
    LOG(ERROR) << "Fail to create bthread for part1";
    return false;
  }
  if (bthread_start_background(&th2, NULL, part2, part2_args) != 0) {
    LOG(ERROR) << "Fail to create bthread for part2";
    return false;
  }
  part3(part3_args);
  bthread_join(th1);
  bthread_join(th2);
  return true;
}
```

这么实现的point：

- 你当然可以建立三个bthread分别执行三个部分，最后join它们，但相比这个方法要多耗费一个线程资源。
- bthread从建立到执行是有延时的（调度延时），在不是很忙的机器上，这个延时的中位数在3微秒左右，90%在10微秒内，99.99%在30微秒内。这说明两点：计算时间超过1ms时收益比较明显。如果计算非常简单，几微秒就结束了，用bthread是没有意义的。尽量让原地运行的部分最慢，那样bthread中的部分即使被延迟了几微秒，最后可能还是会先结束，而消除掉延迟的影响。并且join一个已结束的bthread时会立刻返回，不会有上下文切换开销。
