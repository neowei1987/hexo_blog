---
title: 网站安全系列-XSS攻击
date: 2021-03-09 14:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
---

XSS（Cross-site request forgery）跨站请求伪造

## 核心原理

攻击者通过表单，提交了**一段带有攻击性的JS代码**作为用户要提交的数据。

我们的服务器会把它存起来。

当这段数据被加载到浏览器中渲染时，会被浏览器无条件的当成HTML代码(With JS)来执行渲染。

## 防范实践

### 防范手段

对从数据库中读取的数据，进行URL转义处理；

而不要：存的时候进行转义；

我们的原则一般是：尽量保持信息不丢失。

### 最佳实践


## 参考文章
