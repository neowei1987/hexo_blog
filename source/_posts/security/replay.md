---
title: 网站安全系列-防重放攻击&防篡改
date: 2021-01-15 14:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
---

第一个点：如何防止给服务端的内容被黑客抓取，并查看里面的内容？

客户端每次加密前，都随机生成一个AES key，我们计为：AES_Key
同时请求服务端，获取服务端RSA的公钥，我们计作：RSA_Public(服务端持有用于加密的私钥RSA_Private)

客户端使用RSA非对称加密算法对AES_Key进行加密，得到Encrypt_AES_Key=RSA_Encrypt(AES_Key, RSA_Public) ---由于黑客不可能知道我们的私钥，所以他不可能知道客户端本地AES_Key

客户端使用利用AES对称加密算法对要传输的内容（计作123456, OriginContent），得到Encrypt_Content = AES_Encrypt(AES_Key, OriginContent) ---由于黑客很难知道我们的AES_Key，所以他不可能知晓原始内容

那黑客可以篡改请求吗？
例如把前面的12345，转换为54321？

如果黑客知道私钥(硬编码)

https://cloud.tencent.com/developer/article/1175758