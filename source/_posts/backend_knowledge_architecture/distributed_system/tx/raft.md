https://blog.csdn.net/yangmengjiao_/article/details/120191314

raft将共识问题分解成两个相对独立的问题，leader election，log replication。

### leader选举

election timeout

The election timeout is the amount of time a follower waits until becoming a candidate.

选举时间到了之后，starts a new election term

If the receiving node **hasn't voted yet in this term** then it votes for the candidate...

heartbeat timeout

MESSAGE: Append Entries

This election term will continue until a follower stops receiving heartbeats and becomes a candidate.
【如果一个follower没有及时收到来自leader的heartbeat，那他就会成为一个candidate，申请成为leader】

【每一个任期，进行多数派选举】

可以看出所有节点启动时都是follower状态；在一段时间内如果没有收到来自leader的心跳，从follower切换到candidate，发起选举；如果收到majority的造成票（含自己的一票）则切换到leader状态；如果发现其他节点比自己更新，则主动切换到follower。

总之，系统中最多只有一个leader，如果在一段时间里发现没有leader，则大家通过选举-投票选出leader。leader会不停的给follower发心跳消息，表明自己的存活状态。如果leader故障，那么follower会转换成candidate，重新选出leader。

leader election约束：

1. 同一任期内最多只能投一票，先来先得
2. 选举人必须比自己知道的更多（比较term，log index）

### log replication

1. first appended to the leader's log
    [set 5， add 2]
2. then the change is sent to the followers on the next heartbeat by **Append Entries**
3. 如果多数accept, 则commit； 否则保持为uncommited

leader append log entry
leader issue AppendEntries RPC in parallel
leader wait for majority response
leader apply entry to state machine
leader reply to client
leader notify follower apply log

网络恢复后，如果有更高任期的leader， 则step down。 之前的需要被rollback

流程是先选举出leader，然后leader负责复制、提交log（log中包含command）

为了在任何异常情况下系统不出错，即满足safety属性，对leader election，log replication两个子问题有诸多约束

log replication约束：

一个log被复制到大多数节点，就是committed，保证不会回滚
leader一定包含最新的committed log，因此leader只会追加日志，不会删除覆盖日志
不同节点，某个位置上日志相同，那么这个位置之前的所有日志一定是相同的
Raft never commits log entries from previous terms by counting replicas.
