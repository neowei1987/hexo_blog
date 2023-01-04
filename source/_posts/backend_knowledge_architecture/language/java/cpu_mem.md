---
title: 问题排查系统命令
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
---

top 查看cpu使用率，重点关注：内核还是用户态、load值

cpu使用率2500%左右(40核系统，但平时才300%左右)，并确认当前系统load值是否很高，如果很高(超过cpu核数)，说明当前系统出现大量线程排队现象，如果load比较低但cpu很高，说明系统运行很顺畅，而是业务比较繁忙导致。

top -H pid 查看哪些线程cpu占比高

jstat -gc pid 查看java内部状态

jstack 查看调用stack 

strace 查看系统调用

查看函数/接口耗时

调整jvm 内存参数，调整gc方式（cms->g1)

arthas

dashboard：当前系统的实时数据面板

thread：查看当前 JVM 的线程堆栈信息

jvm：查看当前 JVM 的信息

sc：查看JVM已加载的类信息

sm：查看已加载类的方法信息

jad：反编译指定已加载类的源码

classloader：查看classloader的继承树，urls，类加载信息，使用classloader去getResource

monitor：方法执行监控

watch：方法执行数据观测

trace：方法内部调用路径，并输出方法路径上的每个节点上耗时

stack：输出当前方法被调用的调用路径

tt：方法执行数据的时空隧道，记录下指定方法每次调用的入参和返回信息，并能对这些不同的时间下调用进行观测

reset：重置增强类，将被 Arthas 增强过的类全部还原，Arthas 服务端关闭时会重置所有增强过的类

quit：退出当前 Arthas 客户端，其他 Arthas 客户端不受影响

shutdown：关闭 Arthas 服务端，所有 Arthas 客户端全部退出

---

memory 各种查看

---

netstat 查看timewait closewait, 查看数据包长什么样，是否符合预期等
