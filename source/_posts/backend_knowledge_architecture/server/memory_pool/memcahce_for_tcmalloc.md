---
title: 内存池系列｜TCMalloc分析
tags: 
- 高性能服务器
- 内存池
---

实现要点

1. 分层（ThreadCache, CentralCache, PageCache)
2. 线程局部存储来管理ThreadCache
3. 通过基于hash的freelist来管理小对象
4. 通过radix tree来管理分配出来的obj到span的映射，如此来方便做回收【对象地址到span的映射】
5. 通过buddy算法来管理span, 保证用来分配内存的span尽可能的大（大的**总是**可以通过分裂成为小的，小的只有在**合适的时机-内存连续**才能合并成为大的）

一、ThreadCache

线程分配内存时，TCMalloc从该线程的线程缓存（Thread Cache）中取出恰当尺寸的内存块。而线程释放回线程缓存的内存，也会由垃圾回收机制收纳回中央堆区（Central Heap）。具体地，TCMalloc的内存分配分两种情况：

FreeList list[kClassSizesMax]
每个class一个桶，每个桶中是一个FreeList单链表，将所有该class的对象都链接起来。另外还有一个ThreadCache的prev和next指针，主要用来做数据统计用。

### CentralCache

CentralCache是所有线程共同使用的公共小对象池

CentralCache由一些CentralFreeList组成，每个CentralFreeList管理一个class的小对象，线程在访问CentralCache的时候需要加锁，锁的粒度是每个对象桶CentralFreeList。

### PageHeap

PageHeap是page级别的allocator，它的主要职责就是管理page，上文中提到的span，就是若干连续page组成的数据结构。

PageHeap的核心数据结构有：

PageHeap的核心数据结构有：
1）名为pagemap_的PageMap，它是用来映射Page地址PageID和Span的。这是一个三层的radix_tree，提供的最主要的接口有两个，一是名为set的设置PageID和Span的映射，另一个是名为get的通过PageID获取Span。
【PageId = 内存地址/4K】 Span表示连续几页可用。

2）名为free_[kMaxPages]的一个SpanList数据，kMaxPages在4k页的系统中是255，所以free_中有1个Page到255个Page的所有规格，span可以按照任意大小进行拆分和组合。

3）名为large_的SpanList，它用来存放大于kMaxPages的超大Page。

空闲span的伙伴系统为上层提供span的分配与回收。当需要的span没有空闲时，可以把更大尺寸的span拆小（如果大的span都没有了，则需要重新找kernel分配）；当span回收时，又需要判断相邻的span是否空闲，以便将它们组合。判断相邻span还是要用到radix tree，radix tree就像一个大数组，很容易取到当前span前后相邻的span。

在向tcmalloc申请n个page的Span的时候，优先从free_数组的第n个下标开始寻找，如果free_[n]链表非空，就从这个链表中摘取一个元素，否则，从第n+1个下标开始寻找第一个空闲span，找到后将它切分成n个Page和K个Page，n个Page返回给应用，K个Page插入到free_[k]链表中，如果依然找不到空闲Span，就向操作系统申请一大块内存再分配。

每个SpanList由两个Span链表组成，一个是normal，一个是returned。normal链表是正常的空闲链表，returned链表是将要归还给操作系统的Span组成的空闲链表。在使用MallocExtension::GetStats打印出来tcmalloc的内存占用信息中，free_bytes统计来自normal链表，unmapped_bytes统计来自returned链表。

内存的分配过程
根据请求size判断是大块内存还是小块内存（256KB为边界，这个信息通过查询SizeMap表获得）
1，小块内存
     1), 通过size从SizeMap表中查到改请求对应的classid
     2), 从当前线程所在的ThreadCache的list_[classid]空闲链表中分配，如果分配成功则返回
     3), 尝试从CentralCache.list[class]空闲链表中一次性批发一批空闲object，返回一个给用户，其余的加入到ThreadCache.list_[class]空闲链表中。
     CentralFreeList中申请一批空闲object的申请顺序是：
     1) 优先从tc_slots中获取该数量的objects，tc_slots是一批空闲object的Cache，获取到则返回
     2) 从nonempty_链表中获取一个span，从该span中截取该数量的一批Objects，如果截取完毕之后span内的objects都用完了，那么将这个span插入到empty_链表中，否则增加span的引用计数，增加的数量是object的数量，获取到足够数量则返回
     3) 从nonempty_链表中尝试获取足量objects
     4) 向PageHeap申请若干个Page作为一个span，然后从span中截取足量的Objects，将截取完毕之后的span加入到nonempty_链表中
     PageHeap中申请n个Page的顺序是：
     1) 从PageHeap的free_[n]开始寻找空闲Span，首先尝试从free_[n].normal链表中寻找一个空闲Span，找到后从这个Span中截取n个Page返回，剩下的Page放入到对应的free_[x]链表中; 如果normal中获取不到，那么从free_[n].returned链表中寻找一个空闲的Span，然后做切分的操作。free[n]中找不到，从free[n+1]开始找，直到free[kMaxPages]
     2) 从large_链表中寻找，依然是先normal链表，再returned链表，找到后做切分的操作
     3) 尝试从操作系统申请一块至少kMaxPages大小的内存，继续1) 2)中的步骤
2，大块内存
     大块内存首先计算出需要多少个Page，然后从PageHeap中申请n个Page，流程同上。
 
内存的回收流程
    1，通过ptr的地址找到它所在的Page。对于4k Page的系统来说，每个地址除以4k就是它对应的PageId。
     2，通过PageId在pageheap中找到它对应的Span数据结构，从Span中获取到object所属的class。
    3，如果上面的Span中记录的class是0，说明这是一块大内存，直接调用PageHeap.Delete(Span*)来释放这块大内存；否则是一块小内存，小内存的回收：
        3.1 将这块内存插入到ThreadCache.freeList[cl]链表中，如果发现插入后的总长度大于了max_length，则尝试将若干个objects集体回收到centralCache中。
        3.2 尝试将这些Objects放入centralCache[cl]的FreeList中，如果发现centrailCache[cl]的FreeList已经有足够多的元素，则将这些objects集体回收到span中（通过调用ReleaseListToSpans(start)实现）。
        3.3 通过start地址找到pageId，然后在pageheap中通过PageId找到这些objects所属的span，将这些对象都插入到span->objects列表中。这一步中如果发现这个span上的objects都没有使用者了，就调用PageHeap.Delete(Span*)来释放这个Span。
 
     4， 释放Span：
        4.1 将这个span尝试放入到normal_freelist中。这个过程中，会尝试将pageheap中与此span内存地址相邻的span做合并，之后将合并后的span插入到free_[span->length]链表（小于128个page）或large_链表（大于128个page）中
        4.2 调用PageHeap::IncrementalScavenge(span->length)尝试去归还一部分Span给系统，并将这个Span插入到free_[span->length]链表或者large_链表的returned队列中。
        TCMalloc调用内存释放的接口TCMalloc_SystemRelease，它对应的系统调用的接口是madvise()，建议系统的行为是MADV_FREE，而MADV_FREE则将这些页标识为延迟回收。当内核内存紧张时,这些页将会被优先回收，如果应用程序在页回收后又再次访问，内核将会返回一个新的并设置为0的页。而如果内核内存充裕时，标识为MADV_FREE的页会仍然存在，后续的访问会清掉延迟释放的标志位并正常读取原来的数据，因此应用程序不检查页的数据，就无法知道页的数据是否已经被丢弃。
      因为 Linux 不支持 MADV_FREE，所以使用了 MADV_DONTNEED。使用 MADV_DONTNEED调用 madvise，告诉内核这段内存今后"很可能"用不到了，其映射的物理内存尽管拿去好了，因此，TCMalloc_SystemRelease 只是告诉内核，物理内存可以回收以做它用，但虚拟空间还留着，下次访问时会产生缺页中断，这个缺页中断会触发重新申请物理内存的操作。
      因此Span returned队列中的内存还是可以重新被上层模块申请使用的。

具体参考： https://www.cnblogs.com/cobbliu/p/10854226.html

“基数树”一般用于长整数到对象的映射，而 Trie 树一般用于字符串到对象的映射。