---
title: 云游戏
date: 2022-12-07 10:05:03
updated:
description: 
mathjax: true
categories:
tags: 
- 系统设计
- CDN
---

## 0. 云游戏场景描述

云游戏指在云服务器端运行的游戏，不仅需要将渲染后的游戏画面推送到终端，还需要将终端操作的指令传输到云端服务器进行处理。这种实时交互的需求，使得云游戏对网络时延有较高的要求，需要在尽量靠近用户终端的位置提供服务。

<!-- more -->

## 1. 云游戏解决方案

通过将云游戏服务部署在边缘计算机器，业务可以在靠近用户的位置提供云游戏服务。达到网络传输距离的缩减，显著降低网络时延，满足云游戏双向数据传输对网络时延的苛刻要求。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.3wo7tdjjceg0.webp)