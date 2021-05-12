---
title: 如何为Maven配置国内镜像资源
date: 2020-05-19 17:44:59
tags: 
---

## 为什么需要为Maven配置国内镜像资源

Maven是很流行的项目管理工具，但是由于国外的仓库经常连接不上，即便是连接上，下载速度也很慢。所以，我们需要寻求一个解决方案？

## 解决方案

为Maven配置国内镜像资源

<!-- more -->

## 解决步骤

### 下载Maven, 并配置环境相应的环境变量

1. 下载安装maven
2. 添加环境变量，并设置使之生效

``` java
brew install maven
```

```sh
export MAVEN_HONE=/usr/local/Cellar/maven/3.6.2/
PATH=$MAVEN_HONE/bin:$PATH:
```

### 修改maven setting配置

1. 找到配置文件地址：$MAVEN_HONE/libexec/conf/settings.xml
2. 编辑文件，添加以下内容：

```xml
     <mirror>
        <id>alimaven</id>
        <mirrorOf>central</mirrorOf>
        <name>aliyun maven</name>
        <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
        </mirror>
```

![file](http://graph.baidu.com/resource/222f02fd6561b69f87ee901589881351.png)
