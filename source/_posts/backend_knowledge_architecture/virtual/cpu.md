---
title: 虚拟化篇之CPU虚拟化
date: 2023-1-6 09:03:03
updated:
description: 
mathjax: true
categories:
tags: [知识体系]
---

#### CPU 软件虚拟化

CPU 软件虚拟化#
基于软件的 CPU 虚拟化，故名思议，就是通过软件的形式来模拟每一条指令。通过前面的文章我们知道常用的软件虚拟化技术有两种：优先级压缩和二进制代码翻译。这两种是通用技术，可以用在所有虚拟化类型中。我们就结合 intercept 和 virtualize 来看看 CPU 软件虚拟化是怎么做的。

首先，一些必须的硬件知识要知道，X86 体系架构为了让上层的软件（操作系统、应用程序）能够访问硬件，提供了四个 CPU 特权级别，Ring 0 是最高级别，Ring 1 次之，Ring 2 更次之，Ring 3 是最低级别。

一般，操作系统由于要直接访问硬件和内存，因此它的代码需要运行在最高级别 Ring 0 上，而应用程序的代码运行在最低级别 Ring 3 上，如果要访问硬件和内存，比如设备访问，写文件等，就要执行相关的系统调用，CPU 的运行级别发生从 Ring 3 到 Ring 0 的切换，当完成之后，再切换回去，我们熟悉的用户态和内核态切换的本质就来自这里。

虚拟化的实现也是基于这个思想，VMM 本质上是个 Host OS，运行在 Ring 0 上，Guest OS 运行在 Ring 1 上，再往上是相应层次的应用程序运行在 Ring 2 和 Ring 3 上。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.6nvb5am6en80.webp)

当 Guest OS 或上层应用在执行相关的**特权指令**时，就会发生越权访问，触发异常，这个时候 VMM 就截获（intercept）这个指令，然后模拟（virtualize）这个指令，返回给 Guest OS，让其以为自己的特权指令可以正常工作，继续运行。整个过程其实就是优先级压缩和二进制代码翻译的体现。

<!-- more -->

上面的这种截获再模拟的纯软件的虚拟化方式，势必是性能非常低的。那怎么样提高性能呢，有一种改进的方式是修改 Guest OS 中关于特权指令的相关操作，将其改为一种函数调用的方式，让 VMM 直接执行，而不是截获和模拟，这样就能在一定程度上提高性能。

但这种方式并不通用，要去改 Guest OS 的代码，只能看作是一种定制。为了能够通用，又能够提高性能，就只能从硬件上去做文章了。所以，后来，以 Intel 的 VT-x 和 AMD 的 AMD-V 为主的硬件辅助的 CPU 虚拟化就被提出来（Intel VT 包括 VT-x （支持 CPU 虚拟化）、EPT（支持内存虚拟化）和 VT-d（支持 I/O 虚拟化））。

![image](https://cdn.staticaly.com/gh/neowei1987/blog_assets@main/image.6rmlkjh6bmk0.webp)

CPU 硬件辅助虚拟化在 Ring 模式的基础上引入了一种新的模式，叫 VMX 模式。它包括根操作模式（VMX Root Operation）和非根操作模式（VMX Non-Root Operation）。

这两种模式都有 Ring 0 - Ring 3 的特权级。所以，在描述某个应用程序时，除了描述其属于哪个特权级，还要指明其处于根模式还是非根模式。

引入这种模式的好处就在于，Guest OS 运行在 Ring 0 上，就意味着它的核心指令可以直接下达到硬件层去执行，而特权指令等敏感指令的执行则是由硬件辅助，直接切换到 VMM 执行，这是自动执行的，应用程序是感知不到的，性能自然就提高了。

这种切换 VT-x 定义了一套机制，称为 VM-entry 和 VM-exit。从非根模式切换到根模式，也就是从 Guest 切换到 Host VMM，称为 VM-exit，反之称为 VM-entry。

VM-exit ： 如果 Guest OS 运行过程中遇到需要 VMM 处理的事件，比如中断或缺页异常，或者主动调用 VMCALL 指令调用 VMM 服务的时候（类似于系统调用），硬件自动挂起 Guest OS，切换到根模式，VMM 开始执行。

VM-entry： VMM 通过显示调用 VMLAUNCH 或 VMRESUME 指令切换到非根模式，硬件自动加载 Guest OS 的上下文，Guest OS 开始执行。
