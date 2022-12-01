---
title: java语言-spring
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
### spring cloud 组件

euraka

robbin

hystrix

Zuul

config

Feign



### AOP 切面编程

在不侵入业务代码的情况下，实现日志打印、登录鉴权等功能。

动态代理技术，标准JDK动态代理 OR CGLIB代理

### spring VS  spring MVC VS  spring BOOT
Spring 框架就像一个家族，有众多衍生产品例如 boot、security、jpa等等。但他们的基础都是Spring 的 ioc和 aop ioc 提供了依赖注入的容器 aop ，解决了面向横切面的编程，然后在此两者的基础上实现了其他延伸产品的高级功能。Spring MVC是基于 Servlet 的一个 MVC 框架 主要解决 WEB 开发的问题，因为 Spring 的配置非常复杂，各种XML、 JavaConfig、hin处理起来比较繁琐。于是为了简化开发者的使用，从而创造性地推出了Spring boot，约定优于配置，简化了spring的配置流程。说得更简便一些：Spring 最初利用“工厂模式”（DI）和“代理模式”（AOP）解耦应用组件。大家觉得挺好用，于是按照这种模式搞了一个 MVC框架（一些用Spring 解耦的组件），用开发 web 应用（ SpringMVC ）。然后有发现每次开发都写很多样板代码，为了简化工作流程，于是开发出了一些“懒人整合包”（starter），这套就是 Spring Boot。

Spring MVC的功能Spring MVC提供了一种轻度耦合的方式来开发web应用。Spring MVC是Spring的一个模块，式一个web框架。通过Dispatcher Servlet, ModelAndView 和 View Resolver，开发web应用变得很容易。解决的问题领域是网站应用程序或者服务开发——URL路由、Session、模板引擎、静态Web资源等等。


### IOC 

inversion of control

DI 依赖注入

第三方容器来管理，底层实现是基于反射。

### 循环依赖的解决

通过三个map（一级，二级，三级）创建中的对象数组
只能解决通过set + 单例模式； 无法解决：基于构造函数的循环依赖、通过set + 多例模式