---
title: 缓存简要说明
date: 2022-02-16 23:20:03
updated:
mathjax: true
categories:
tags: 
---

高速缓存服务器(Cache Server)是软硬件高度集成的专业功能服务器，主要做高速缓存加速服务，一般部署在网络边缘。

根据加速对象不同，分为客户端加速和服务器加速

客户端加速Cache部署在网络出口处，把常访问的内容缓存在本地，提高响应速度和节约带宽;

服务器加速Cache部署在服务器前端，作为Web服务器的前置机，提高Web服务器的性能，加速访问速度。

---

缓存有哪些类型？

- 服务器LocalCache （有状态）

将缓存内容放到服务器的本地内存或者磁盘；

无法及时更新，一般都是设置一个合理的过期时间，让其自动过期；适用于实时性要求不高的场景

特例：数据库缓存

- 分布式缓存（无状态）

redis\memcache\tair

- 客户端缓存（有状态）

具体有哪些：
浏览器cookie；浏览器本地缓存；flash本地存储；html5的本地存储；native app 本地缓存
缓存系统对比与选型

---

在Web应用领域，Web缓存大致可以分为以下几种类型：

#### 浏览器端缓存

浏览器缓存根据一套与服务器约定的规则进行工作，在同一个会话过程中会检查一次并确定缓存的副本足够新。如果你浏览过程中，比如前进或后退，访问到同一个图片，这些图片可以从浏览器缓存中调出而即时显现。

客户端浏览器缓存主要是通过在http头部增加
Last-Modified,If-Modified-Since,Expires,Cache-Control等标识，和服务器进行协商，是否是采用客户的本机缓存来实现。

其中这里面也会分为三种方式

1 通过Last-Modified，If-Modified-Since方式和服务器通信，客户发出http请求中包含If-Modified-Since，如果服务器端代码没有修改，服务器端返回302响应代码的请求响应头（内容不返回）客户端则直接用本机缓存的内容缓存显示结果。相
当于节省了服务器执行代码时间以及数据传输时间。

2 通过Expires,Cache-Control控制，客户端发现如果上次请求的页面还未过期，通过Expires或者Cache-Control进行辨别，则直接显示本机缓存的内容，不与服务器进行通信。

#### 服务器端缓存

##### CDN缓存

CDN（Content delivery networks）缓存，也叫网关缓存、反向代理缓存。CDN缓存一般是由网站管理员自己部署，为了让他们的网站更容易扩展并获得更好的性能。浏览器先向CDN网关发起Web请求，网关服务器后面对应着一台或多台负载均衡源服务器，会根据它们的负载请求，动态将请求转发到合适的源服务器上。虽然这种架构负载均衡源服务器之间的缓存没法共享，但却拥有更好的处扩展性。从浏览器角度来看，整个CDN就是一个源服务器，从这个层面来说，本文讨论浏览器和服务器之间的缓存机制，在这种架构下同样适用。

##### 代理服务器缓存

代理服务器是浏览器和源服务器之间的中间服务器，浏览器先向这个中间服务器发起Web请求，经过处理后（比如权限验证，缓存匹配等），再将请求转发到源服务器。代理服务器缓存的运作原理跟浏览器的运作原理差不多，只是规模更大。可以把它理解为一个共享缓存，不只为一个用户服务，一般为大量用户提供服务，因此在减少相应时间和带宽使用方面很有效，同一个副本会被重用多次。常见代理服务器缓存解决方案有Squid等

##### Web应用层缓存

应用层缓存指的是从代码层面上，通过代码逻辑和缓存策略，实现对数据，页面，图片等资源的缓存，可以根据实际情况选择将数据存在文件系统或者内存中，减少数据库查询或者读写瓶颈，提高响应效率。

##### 数据库数据缓存

Web应用，特别是SNS类型的应用，往往关系比较复杂，数据库表繁多，如果频繁进行数据库查询，很容易导致数据库不堪重荷。为了提供查询的性能，会将查询后的数据放到内存中进行缓存，下次查询时，直接从内存缓存直接返回，提供响应效率。比如常用的缓存方案有memcached等。

总结一下：
一般的高并发的应用程序，都在web层采用了以上几种缓存，一般静态资源（图片，js，css）都会采用nginx反向代理+客户端缓存来实现
对于门户网站，尤其是首页的新闻，一般都会缓存起来，可以通过反向代理也可以通过应用程序缓存实现方式
对于下载或者视频网站，由于数据传输比较大，直接采用浏览器本地缓存实现。

---

业务需求可能涉及的缓存组件要求：

##### 容量

需要存储什么类型的内容？ 存储量多大？

##### 并发（qps)

缓存的读写比例以及qps如何？

##### 响应时间

更高的qps可以通过扩容来解决，但是一次响应的时间是有限制的，例如跨机房访问延迟0.5ms，就决定了响应时间不可能低于0.5ms;

反过来，如果业务上要求的resp time必须小于0.5ms， 那么该缓存就一定满足不了我们的要求。

##### 使用成本

分为两部分：

1. 首先服务端，主要包括：运维成本、机器成本
2. 第二，客户端，主要包括程序员研发成本：单一的库依赖、简洁的配置和人性化的API丰富的文档和技术支持

##### 扩展性要求

在某方面出现瓶颈（qps或者容量）时，能否通过增加机器来快速在线扩容；这个主要涉及到系统的负载均衡能力；

##### 容灾能力

缓存数据丢失；不同的系统有不同的容灾能力；一定要结合业务需求

---

