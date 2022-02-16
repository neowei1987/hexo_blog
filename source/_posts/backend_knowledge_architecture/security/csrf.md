---
title: 网站安全系列-CSRF攻击
date: 2021-01-15 14:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
---

CSRF（Cross-site request forgery）跨站请求伪造

## 核心原理

浏览器在请求接口时有如下机制：
**浏览器**请求某域名下的某个接口时，会**自动带上该域名下的Cookies**，而不管发起请求的页面是究竟在在哪个域名下。

基于以上机制，攻击者只要有目的的部署自己的攻击方式，便能够让真正的用户在**不知情的情况下**完成某些操作，例如：给攻击者点赞、给攻击者转账等。

攻击方式：

- GET类型
  - 伪造图片
  - 伪造超链接
- POST类型
  - 页面加载自动提交POST表单

## 防范实践

### 防范手段

- 每次发起请求时，从页面元素中拿取一个由服务端动态下发的token
- 每次发起请求时，从cookies中拿取一个由服务端种好的token
- 检查refer是否符合预期（问题是不是所有的合法请求都有refer)
- 浏览器SameSite机制：lex

### 最佳实践

一般情况下，我们可以这么做取防范CSFR攻击：

- 明确GET/POST的最基本语义，并严格遵守（不要出现GET接口完成写操作的情况）
- 写入代表登陆态的Cookies时，使用SameSite的lex模式

## 参考文章

https://www.netsparker.com/blog/web-security/same-site-cookie-attribute-prevent-cross-site-request-forgery/
https://www.jianshu.com/p/66f77b8f1759
https://tech.meituan.com/2018/10/11/fe-security-csrf.html