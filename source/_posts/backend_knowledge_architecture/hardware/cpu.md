---
title: 计算机硬件-CPU寄存器简介
date: 2022-12-06 22:18:03
mathjax: true
categories:
- 
tags: 
- 计算机硬件
---

## CPU寄存器

在用途方面，他们有各自默认的用途：

- Eax用来保存所有API函数的返回值。寄存器AX和AL通常称为累加器(Accumulator)，用累加器进行的操作可能需要更少时间。累加器可用于乘、除、输入/输出等操作，它们的使用频率很高；
- 寄存器BX称为基地址寄存器(Base Register)。它可作为存储器指针来使用；
- 寄存器CX称为计数寄存器(Count Register)。在循环和字符串操作时，要用它来控制循环次数；在位操作中，当移多位时，要用CL来指明移位的位数；
- 寄存器DX称为数据寄存器(Data Register)。在进行乘、除运算时，它可作为默认的操作数参与运算，也可用于存放I/O的端口地址。

寄存器ESI、EDI、SI和DI称为变址寄存器(Index Register)，

它们主要用于存放存储单元在段内的偏移量，用它们可实现多种存储器操作数的寻址方式，为以不同的地址形式访问存储单元提供方便。

那么ESP和EBP指的分别是什么呢？

- ESP：栈指针寄存器(extended stack pointer)，其内存放着一个指针，该指针永远指向系统栈最上面一个栈帧的栈顶。
- EBP：基址指针寄存器(extended base pointer)，其内存放着一个指针，该指针永远指向系统栈最上面一个栈帧的底部。

对于64位CPU，EAX ---> RAX
### CPU指令的执行

一个基本的CPU执行计算的过程如下：

1. 程序以及数据被加载到主内存
2. 指令和数据被加载到CPU的高速缓存
3. CPU执行指令，把结果写到高速缓存
4. 高速缓存中的数据写回主内存

### 一次函数调用

栈的增长方向：向下增长，ESP越来愈小、ESP比EBP小

一个函数执行步骤：

1. 函数参数压入stack中
    push p1
    push p2
2. CPU**自己**把返回地址压入stack中
    push eip
3. CPU自己跳转到新的函数地址(call func)，开始执行（先保存EBP，然后让EBP指向当前ESP）
    push ebp 保存老函数的EBP到新的stack中
    mov esp => ebp  让ebp保存新函数的stack base
4. 分配局部变量
    sub esp 100 分配100字节的局部变量
5. 局部变量赋值与访问
    通过ebp - $Offset$ 来访问局部变量
6. 访问参数
    通过ebp + $Offset$ 来访问参数
7. 函数返回
    add esp 100
    mov ebp => esp
    注意：上面这一句应该是重复的，理论上只要对esp进行了完成逆操作，esp应该等于ebp了。是不需要额外通过ebp来还原的；当然如果要通过ebp来还原，也就不需要去显示操作esp了。
    pop ebp 还原ebp
    ret（pop eip）
8. 将压入的参数POP出来
    pop p2
    pop p1

## 指令集

 所谓指令集，是CPU中用来计算和控制计算机系统的一套指令的集合。指令的强弱是CPU的重要指标，指令集是提高微处理器效率的最有效工具之一。

CPU依靠指令来计算和控制系统，每款CPU在设计时就规定了一系列与其硬件电路相配合的指令系统。与其他硬件电路相配合，决定的是这一款CPU的生态系统。因此，指令集搭建的是一个桥梁，是软硬件之间沟通的桥梁，简单来说，软件通过指令集和硬件讲话。因此，指令集对形成生态至关重要，从这个意义上讲，不同的CPU指令集，决定了这款CPU设计的复杂程度。

从现阶段的主流体系结构讲，指令集可分为复杂指令集(CISC, complex instruction set computer)和精简指令集(RISC, reduced instruction set computer)两部分。简单来讲，RISC功能简洁，代表着简洁的CPU设计，CISC功能完备，代表着复杂的CPU设计。
这里引用步日欣老师文章中的一段话：

    CPU的指令，就如同盖房子的砖，如果都是小块的标准砖头，也能盖起各种不同的房子，这就是RISC；
    如果除了标准砖头，还设计了很多的砖瓦结构件，适用于拐角、吊梁等，这就是CISC。
    不同的模式，都能盖起房子，但是效率却大不一样，RISC的标准砖头，小平房可以盖，
    摩天大楼也可以盖，底层的原材料很简单，都是标准化的砖头；
    CISC的各种复杂的结构件，对于盖一种房子的时候效率确实高，吊起结构件随便一拼装就ok，
    但是如果要盖的房子种类多了，就需要定义更多更复杂的结构件，结构件的管理就会越来越复杂，
    而且在建设某种常见建筑的时候，大部分特殊的结构架是闲置不用的，大大影响了施工效率。
    基于CISC模式下的CPU设计，在各种新需求下，堆叠的功能越来越复杂，芯片设计难度也越来越高，效率低下，
    因此就出现了RISC精简指令集的概念。

### 对比CISC和RISC

CISC的指令能力强，单多数指令使用率低却增加了CPU的复杂度，指令是可变长格式；RISC的指令大部分为单周期指令，指令长度固定，操作寄存器，只有Load/Store操作内存

CISC支持多种寻址方式；RISC支持方式少

CISC通过微程序控制技术实现；RISC增加了通用寄存器，硬布线逻辑控制为主，是和采用流水线

CISC的研制周期长

RISC优化编译，有效支持高级语言

大白话就是：

CISC架构，性能好，但是耗电多，电压高。主要用于桌面服务。

RISC架构：耗电少，电压低，但是单核性能比不上CISC架构，主要用于嵌入式开发，或者移动设备开发。

### CPU架构

1. ARM架构，过去称作进阶精简指令集机器（Advanced RISC Machine，更早称作：Acorn RISC Machine），是一个32位精简指令集（RISC）处理器架构

2. x86或80x86是英代尔Intel首先开发制造的一种微处理器体系结构的泛称。x86架构是重要地可变指令长度的CISC（复杂指令集电脑，Complex Instruction Set Computer）。

3. MIPS是世界上很流行的一种RISC处理器。MIPS的意思是“无内部互锁流水级的微处理器”(Microprocessor without interlockedpipedstages)

4. PowerPC 是一种精简指令集（RISC）架构的中央处理器（CPU），其基本的设计源自IBM（国际商用机器公司）的IBMPowerPC 601 微处理器POWER（PerformanceOptimized With Enhanced RISC

### intel,amd和arm的关系

Intel 与 AMD是两个公司，amd 与 arm 又是同一个公司（AMD）的两款产品

Intel与AMD共同采用x86架构，都采用CICS指令集，一般用于桌面应用；

而arm 采用 ARM架构，采用RICS指令集，例如家用游戏机、平板、手机等会采用arm CPU

可以说，AMD CPU是 AMD公司为对抗Intel公司的Intel CPU推出的第一代产品；

而 ARM CPU 是AMD公司为了对抗Intel公司的Intel CPU推出的第二代产品，

## co 实现

```cpp
co_ctx{
void* regs[14]; //用于保存或者设定特定寄存器
size_t ss_size; //栈帧区域大小
char* ss_sp; // 协程栈帧内存区域，这个区域一般在堆上分配
}

co_make (co_ctx* co, func* p, p1, p2)
    使用p, p1, p2把co填充起来
    co.ss_sp都是分配在堆上
    co的EIP与ESP需要被单独赋值
}
co_swap（）{
    主要要保存当前寄存器到要swap_out的co_ctx中
    将要swap_in的co_ctx设置到寄存器中
}
```

具体参考：https://vinsflyfish.github.io/posts/thinking-in-libco/