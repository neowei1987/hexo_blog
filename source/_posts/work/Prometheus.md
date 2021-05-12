---
title: 工作杂谈系列-普罗米修斯常用查询
date: 2021-01-15 14:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
---

普罗米修斯字符串匹配查询语法：

=: Select labels that are exactly equal to the provided string.
!=: Select labels that are not equal to the provided string.
=~: Select labels that regex-match the provided string.
!~: Select labels that do not regex-match the provided string.

具体可以看这里：
https://prometheus.io/docs/prometheus/latest/querying/basics/
