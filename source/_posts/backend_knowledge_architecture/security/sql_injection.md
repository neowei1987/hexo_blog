---
title: 网站安全系列-SQL注入
date: 2021-02-15 11:31:03
updated: 2021-02-15 11:44:03
copyright: true
password:
keywords: []
description: 
mathjax: true
categories:
tags:
- 系统安全
---

## 核心原理

where a = '$input'

input 被攻击者蓄意构造，系统服务器执行了不符合预期的SQL语句，从而导致攻击者获取到了更多的的数据。

where a = 'input' or 1=1;

## 防范实践

### 防范手段

对输入进行特殊字符的转义

### 最佳实践

## 参考文章
