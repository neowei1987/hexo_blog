---
title: M1芯片MAC系统安装DPDK避坑指南 
date: 2023-1-6 1:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---

### 0. 问题汇总

#### 问题1:M1芯片MAC系统无法安装预期ubuntu系统

安装不同版本的ubuntu系统，出现不通的问题，总体有两种：

1. BIOS无法识别到CDROM中的ISO镜像
2. 安装系统时，页面卡死在黑屏状态

复现场景：

宿主机器：M1芯片的MAC系统
虚拟机软件：Parellels Desktop 17
ubuntu版本：ubuntu-20.04-live-server-amd64

问题原因：

计算机硬件与操作系统内核版不匹配，Parellels Desktop虚拟化出来的CPU依旧为[M1苹果芯片](https://www.fpthinker.com/backend_knowledge_architecture/hardware/cpu.html)，而安装的镜像为AMD64，两者不是一个体系，所以出现问题。

解决方案：

安装跟硬件匹配的内核版本：ubuntu-XXX-arm64，例如ubuntu-20.04-live-server-amd64

<!-- more -->

#### 问题2:ubuntu系统启动时报EFI相关错误

ubuntu系统启动时，报错如下：

    EFI stub:Booting Linux Kernel...EFI stub:EFI_RNG_PROTOCOL unavailable
    EFI stub:ERROR:FIRMWARE BUG:Image BSS overlaps adjacent EFI memory regionEFI stub:Using DTB from configuration table
    EFI stub:Exiting boot services and installing virtual address map

复现场景：

宿主机器：M1芯片的MAC系统
虚拟机软件：Parellels Desktop 17
ubuntu版本：ubuntu-20.04-live-server-arm64

解决方案：

升级了最新版本Parellels Desktop 18(文末有下载地址），并进行了有效破解（破解非必需）

## 相关下载

### 破解版Parellels Desktop 18 下载地址

[下载链接](https://pan.baidu.com/s/1RpmfPmc86rqpwhVohxUetg)

![头像](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.29ucrvenk9lw.jpg)

扫码关注公众号，回复“PD18”获取提取码。
