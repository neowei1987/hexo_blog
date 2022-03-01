---
title: 网站安全系列-CSRF攻击
date: 2021-02-15 11:31:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags:
- 系统安全
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
- 检查refer是否符合预期（问题是：不是所有的合法请求都有refer)
- 浏览器SameSite机制：lex

#### 同源检测

HTTP头中有一个Referer字段，这个字段用以标明请求来源于哪个地址。在处理敏感数据请求时，通常来说，Referer字段应和请求的地址位于同一域名下。以上文银行操作为例，Referer字段地址通常应该是转账按钮所在的网页地址，应该也位于bank.com之下。而如果是CSRF攻击传来的请求，Referer字段会是包含恶意网址的地址，不会位于bank.com之下，这时候服务器就能识别出恶意的访问。

这种办法简单易行，工作量低，仅需要在关键访问处增加一步校验。但这种办法也有其局限性，因其完全依赖浏览器发送正确的Referer字段。虽然http协议对此字段的内容有明确的规定，但并无法保证来访的浏览器的具体实现，亦无法保证浏览器没有安全漏洞影响到此字段。并且也存在攻击者攻击某些浏览器，篡改其Referer字段的可能。

CSRF大多数情况下来自第三方域名，但并不能排除本域发起。如果攻击者有权限在本域发布评论（含链接、图片等，统称UGC），那么它可以直接在本域发起攻击，这种情况下同源策略无法达到防护的作用。

#### Samesite Cookie

Chrome 51开始，浏览器的Cookie新增加了一个SameSite属性，用来防止CSRF攻击和用户追踪。Samesite有三个可选值，分别为Strict、Lax、None。

Strict：最严格模式，完全禁止第三方Cookie，跨站点访问时，任何情况下都不会发送Cookie。换言之，只有当前网页的 URL与请求目标一致，才会带上Cookie。
此方式虽然安全，但是存在严重的易用性问题，用户从第三方页面访问一个已登录的系统时，由于未携带Cookie，总是需要重新登录。

Lax：Chrome默认模式，对于从第三方站点以link标签，a标签，GET形式的Form提交这三种方式访问目标系统时，会带上目标系统的Cookie，对于其他方式，如 POST形式的Form提交、AJAX形式的GET、img的src访问目标系统时，不到Cookie。
None：原始方式，任何情况都提交目标系统的Cookie。
由于Samesite是Google提出来的，其他浏览器目前并未普及，存在兼容性问题，目前不推荐使用。

#### CSRF Token

由于CSRF的本质在于攻击者欺骗用户去访问自己设置的地址，所以如果要求在访问敏感数据请求时，要求用户浏览器提供不保存在Cookie中，并且攻击者无法伪造的数据作为校验，那么攻击者就无法再运行CSRF攻击。这种数据通常是Form表单中的一个数据项。服务器将其生成并附加在Form中，其内容是一个伪随机数。当客户端通过Form提交请求时，这个伪随机数也一并提交上去以供校验。正常的访问时，客户端浏览器能够正确得到并传回这个伪随机数，而通过CSRF传来的欺骗性攻击中，攻击者无从事先得知这个伪随机数的值，服务端就会因为校验token的值为空或者错误，拒绝这个可疑请求。

CSRF Token需要服务器端对提交的请求进行验证，一般CSRF Token以Session参数的形式保存在服务器端。对于分布式应用，使用分布式Session来管理的难道比较大，可以考虑把Token保存在Redis等分布式缓存中。

双重Cookie验证
上述CSRF Token方式，需要在服务器上保存Token值，并对请求参数进行校验，增加了服务器端的复杂度。双重Cookie验证的原理是在Cookie中保存Token值，同时在Form表单中也提供该值，请求提交时，Cookie和Form表单中的Token同时提交，服务器端只需要对请求中的两个参数进行校验即可，省去了在服务器端维护Token的步骤。

由于Cookie的安全限制，只能在本域名或子域名下访问到Cookie值，兄弟子域名无法访问到，如a.bank.com域名下的Cookie，只能被a.bank.com，sub.a.bank.com访问，无法被b.bank.com访问。对于分布式应用，可能需要在多个子域名中提交请求，所以一般需要把Cookie保存在根域名bank.com中。不过此方式存在安全风险，如果任何一个子域下的页面存在XSS攻击，可导致根域名下的Cookie被篡改，Token可被攻击者任意修改，导致安全措施失效。

### 最佳实践

一般情况下，我们可以这么做取防范CSFR攻击：

- 明确GET/POST的最基本语义，并严格遵守（不要出现GET接口完成写操作的情况）
- 写入代表登陆态的Cookies时，使用SameSite的lex模式

## 参考文章

https://www.netsparker.com/blog/web-security/same-site-cookie-attribute-prevent-cross-site-request-forgery/
https://www.jianshu.com/p/66f77b8f1759
https://tech.meituan.com/2018/10/11/fe-security-csrf.html