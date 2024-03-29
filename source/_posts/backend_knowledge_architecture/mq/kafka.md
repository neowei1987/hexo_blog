---
title: 消息队列-Kafka
date: 2022-02-25 13:06:03
mathjax: true
categories:
- 
tags: 
- 消息队列
---

![设计思想](https://img-blog.csdn.net/20180317011215184?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

#### cosume group

通过cosume group，巧妙的解决了广播问题。

#### 高性能

SendFile、zero copy

#### 索引设计

Kafka为了卸载MQ本身的复杂性，为了其**真正无状态**的设计，它将状态维护机制这口锅完全甩给了消费者，因此取消息的问题就转化成了**消费者拿着一个offset索引来Kafka存储器里取消息**的问题，这就涉及到了性能。But 如何能查的更快？How？

![扫描partition文件](https://img-blog.csdn.net/20180317015646335?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

但实际上，

![partition](https://img-blog.csdn.net/20180317020648952?watermark/2/text/Ly9ibG9nLmNzZG4ubmV0L2RvZzI1MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

1. partition并不是一根文件，而是一个目录
2. 目录下面存了很多逻辑上的segment，每一个segment物理上包括两个文件：索引文件、日志文件（每次都append)

文件的命名相当于查找的稀疏索引，省去索引文件

每个segment索引又是一个稀疏索引减少索引文件的大小

在 Kafka 中，生产者写入消息、消费者读取消息的操作都是与 leader 副本进行交互的，从 而实现的是一种主写主读的生产消费模型。

### 16.为什么Kafka不支持读写分离？

Kafka 并不支持主写从读，因为主写从读有 2 个很明 显的缺点:

(1)数据一致性问题。数据从主节点转到从节点必然会有一个延时的时间窗口，这个时间 窗口会导致主从节点之间的数据不一致。某一时刻，在主节点和从节点中 A 数据的值都为 X， 之后将主节点中 A 的值修改为 Y，那么在这个变更通知到从节点之前，应用读取从节点中的 A 数据的值并不为最新的 Y，由此便产生了数据不一致的问题。

(2)延时问题。类似 Redis 这种组件，数据从写入主节点到同步至从节点中的过程需要经 历网络→主节点内存→网络→从节点内存这几个阶段，整个过程会耗费一定的时间。而在 Kafka 中，主从同步会比 Redis 更加耗时，它需要经历网络→主节点内存→主节点磁盘→网络→从节 点内存→从节点磁盘这几个阶段。对延时敏感的应用而言，主写从读的功能并不太适用。

#### replication

2.1 消息备份

Kafka允许同个Partition存在多个消息副本(Replica)，每个Partition的副本通常由1个Leader及0个以上的Follower组成，产者将消息直接发往对应Partition的Leader，Follower会周期地向Leader发送同步请求，Kafka的Leader机制在保障数据致性地同时降低了消息备份的复杂度。同Partition的Replica应存储在同一个Broker上，因为一旦该Broker宕机，对应Partition的所有Replica都无法作，这就达不到高可用的效果。为做好负载均衡并提容错能，Kafka会尽将所有的Partition以及各Partition的副本均匀地分配到整个集群上。举个例，当集群中部署3台Broker，TopicA共有4个Partition，每个Partition均有3个Replica时下图就是种合理的分布方式。

![](https://pics4.baidu.com/feed/d833c895d143ad4b76bc3f8833f912a7a60f06ef.jpeg)

ISR:In-Sync Replicas 副本同步队列

ISR(In-Sync Replicas)指的是个Partition中与Leader“保持同步”的Replica列表(实际存储的是副本所在Broker的BrokerId)，这的 保持同步是指与Leader数据保持完全一致，只需在replica.lag.time.max.ms时间内与Leader保持有效连接，官方解释如下If a follower hasn't sent any fetch requests or hasn't consumed up to the leaders log end offset for at least this time, the leader will remove the follower from isr,( default value =10000 )Follower周期性地向Leader发送FetchRequest请求(数据结构见下)，发送时间间隔配置在replica.fetch.wait.max.ms中，默认值为 500。

AR:Assigned Replicas 所有副本

ISR是由leader维护，follower从leader同步数据有一些延迟（包括延迟时间replica.lag.time.max.ms和延迟条数replica.lag.max.messages两个维度, 当前最新的版本0.10.x中只支持replica.lag.time.max.ms这个维度），任意一个超过阈值都会把follower剔除出ISR, 存入OSR（Outof-Sync Replicas）列表，新加入的follower也会先存放在OSR中。AR=ISR+OSR。

ISR数据同步、ACK选项（全部ack、只有一个ack）

Kafka的复制机制既不是完全的同步复制，也不是单纯的异步复制。

完全同步复制要求All Alive Follower都复制完，这条消息才会被认为commit，这种复制方式极大的影响了吞吐率。

而异步复制方式下，Follower异步的从Leader复制数据，数据只要被Leader写入log就被认为已经commit，这种情况下，如果leader挂掉，会丢失数据。

kafka使用ISR的方式很好的均衡了确保数据不丢失以及吞吐率。Follower可以批量的从Leader复制数据，而且Leader充分利用磁盘顺序读以及send file(zero copy)机制，这样极大的提高复制性能，内部批量写磁盘，大幅减少了Follower与Leader的消息量差。

leader会维护一个与其基本保持同步的Replica列表，该列表称为ISR(in-sync Replica)，每个Partition都会有一个ISR，而且是由leader动态维护 ，如果一个follower比一个leader落后太多，或者超过一定时间未发起数据复制请求，则leader将其重ISR中移除

#### Log End Offset

当前broker收到的最新offset

#### HighWatermark

已经同步到其他slave中的offset

#### Leader epoch

由于follower的HW的更新，需要一轮额外的消息拉取，如果folloer很多的话，就需要多轮拉取Leader 副本高水位更新和 Follower 副本高水位更新在时间上是存在错配的，会导致数据的
不一致，所以Leader epoch登场。

Epoch，一个单调增加的版本号。每当leader发生变更时，都会增加该版本号。小版本号的Leader 被认为是过期 Leader，不能再行使 Leader权力。

起始位移，Leader 副本在该 Epoch 值上写入的首条消息的位移类似于zookeper的leader机制，通过leader epoch的单调递增，以此避免副本宕机重启导致的消息同步错乱

参考：

https://blog.csdn.net/dog250/article/details/79588437
https://www.jianshu.com/p/469ec6dcdc02
https://blog.csdn.net/qq_28900249/article/details/90346599