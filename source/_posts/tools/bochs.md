---
title: bochs相关
date: 2022-12-25 22:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---
## 0. brew是什么

/usr/local/Cellar/bochs/2.7/share/bochs/BIOS-bochs-latest
/usr/local/Cellar/bochs/2.7/share/bochs/VGABIOS-lgpl-latest
/usr/local/Cellar/bochs/2.7/share/bochs/keymaps/x11-pc-us.map

nasm bootloader.asm -o boot.bin
dd if=boot.bin of=hd64.img bs=512 count=1 conv=notrunc

<!-- more -->

## 1. brew相关问题

Bochs启动不显示窗口

https://www.cnblogs.com/Noura/articles/15212922.html

Mac安装配置bochs

https://blog.csdn.net/SL_World/article/details/124483823

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.13ldqa13tl8g.webp)