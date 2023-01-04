---
title: brew相关
date: 2022-12-25 13:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---
## 0. brew是什么

brew是一款mac系统下的一款应用程序管理软件，个人建议一定要确保自己的brew可以正常工作，通过brew来安装其他程序，而**尽量不要通过源码自行编译安装**，成本高的离谱！

<!-- more -->

## 1. brew相关问题

由于brew安装，需要访问github，而国内访问不通，所以**需要使用代理**，以下是shell中设置代理的方法。

```sh
export https_proxy=http://127.0.0.1:7890 http_proxy=http://127.0.0.1:7890 all_proxy=socks5://127.0.0.1:7890
```

卸载原有brew

```sh
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/uninstall)"
```

安装新的brew

```sh
/bin/zsh -c "$(curl -fsSL https://gitee.com/cunkai/HomebrewCN/raw/master/Homebrew.sh)"
```

brew更新提示：fatal: not in a git directory

homebrew-core和homebrew-cask /opt/homebrew/Library/Taps/homebrew/homebrew-services目录 被git认为不是一个安全的目录，需要手动添加

```sh
git config --global --add safe.directory 你的homebrew-core路径
git config --global --add safe.directory 你的homebrew-cask路径
```
