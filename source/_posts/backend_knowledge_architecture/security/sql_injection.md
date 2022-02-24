---
title: 网站安全系列-SQL注入
date: 2021-03-09 14:49:03
updated:
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
---

where a = 'input' or 1=1;

## 核心原理

where a = '$input'

input 被攻击者蓄意构造，从而导致攻击者获取到了更多的的数据。

## 防范实践

### 防范手段

对输入进行特殊字符的转义

### 最佳实践

## 参考文章
