## TCP协议细节

![](https://img-blog.csdn.net/20171214152607931?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGliYWluZXUyMDA0/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

tcp慢启动过程

TCP拥塞控制

TCP三次握手四次挥手

TCP三次握手的缺陷：Sync Flood攻击

4.TCP如何保证可靠性. 把三次握手很详细地说了一遍,发送什么码进入什么状态..

5.除了三次握手还有么?滑动窗口,1比特等待协议,回退N针协议,选择性重传协议说了一边

6.还有么?不用说的那么详细,时间不太多了 说了 快重传 快恢复 超时重传,然后实在不知道了

### 关于TIME_WAIT存在的必要性

1）为实现TCP全双工连接的可靠释放

由TCP状态变迁图可知，假设发起主动关闭的一方（client）最后发送的ACK在网络中丢失，由于TCP协议的重传机制，执行被动关闭的一方（server）将会重发其FIN，在该FIN到达client之前，client必须维护这条连接状态，也就说这条TCP连接所对应的资源（client方的local_ip,local_port）不能被立即释放或重新分配，直到另一方重发的FIN达到之后，client重发ACK后，经过2MSL时间周期没有再收到另一方的FIN之后，该TCP连接才能恢复初始的CLOSED状态。如果主动关闭一方不维护这样一个TIME_WAIT状态，那么当被动关闭一方重发的FIN到达时，主动关闭一方的TCP传输层会用RST包响应对方，这会被对方认为是有错误发生，然而这事实上只是正常的关闭连接过程，并非异常。

2）为使旧的数据包在网络因过期而消失；防止lost duplicate对后续新建正常链接的传输造成破坏。

为了防止延迟到达的IP包造成数据混乱。两个原因：端口复用，seqno发生环回。

lost duplicate在实际的网络中非常常见，经常是由于路由器产生故障，路径无法收敛，导致一个packet在路由器A，B，C之间做类似死循环的跳转。IP头部有个TTL，限制了一个包在网络中的最大跳数，因此这个包有两种命运，要么最后TTL变为0，在网络中消失；要么TTL在变为0之前路由器路径收敛，它凭借剩余的TTL跳数终于到达目的地。但非常可惜的是TCP通过超时重传机制在早些时候发送了一个跟它一模一样的包，并先于它达到了目的地，因此它的命运也就注定被TCP协议栈抛弃。

另外一个概念叫做incarnation connection，指跟上次的socket pair一摸一样的新连接，叫做incarnation of previous connection。

lost duplicate加上incarnation connection，则会对我们的传输造成致命的错误。

大家都知道TCP是流式的，所有包到达的顺序是不一致的，依靠序列号由TCP协议栈做顺序的拼接；假设一个incarnation connection这时收到的seq=1000, 来了一个lost duplicate为seq=1000, len=1000, 则tcp认为这个lost duplicate合法，并存放入了receive buffer，导致传输出现错误。

通过一个2MSL TIME_WAIT状态，确保所有的lost duplicate都会消失掉，避免对新连接造成错误。