---
title: 函数调用约定
date: 2022-12-06 20:40:03
updated:
description: 
mathjax: true
categories:
tags: [语言底层]
---

## 0. 函数调用约定

|  名称 | 谁来清理入栈参数| 参数压栈顺序 |函数名转换规则|
|  ----  | ---- |----  |----  |
|__stdcall | 被调用函数在返回前清理入栈参数 |参数自右向左压栈 |C语言时，_function@number，number为参数的字节数；C++编译时函数名的转换：?function@@YG****@Z或者?function@@YG*XZ；若函数有参数，以@Z结束；若函数无参数，则以Z结束|
|__cdecl | 调用函数在返回后清理入栈参数 |参数自右向左压栈 |_function，其中function为函数名；C++编译时函数名的转换：同__stdcall，把YG改为YA|
|__fastcall | 被调用函数在返回前清理入栈参数 |使用ECX传递第一个参数，EDX传递第二个参数，其余参数自右向左压栈 |C编译时函数名的转换：@function@number；C++编译时函数名的转换：同__stdcall，把YG改为YI|
|__pascal | 被调用函数在返回前清理入栈参数 |参数自左向右压栈 |较为复杂，参加pascal文档|

<!-- more -->

## 1. thiscall

thiscall不是一个关键字，因此不能在程序中明确指定，它是C++类成员函数缺省的调用约定。由于成员函数调用涉及到一个this指针，因此必须进行特殊处理。

参数自右向左压栈

如果参数个数确定，this指针通过ECX传递给被调用者；如果参数个数不定，this指针在所有参数压栈后被压入堆栈

如果参数个数确定，被调用函数自己清理堆栈；如果参数个数不定，由调用函数清理堆栈

可见，对于参数个数固定情况下，它类似于__stdcall，不定时则类似__cdecl

## 2. naked call

使用前四种调用约定时，在进入函数时编译器会产生代码来保存ESI，EDI，EBX，EBP寄存器，退出函数时则产生代码恢复这些寄存器的内容。

naked call不产生这样的代码。更特殊的是，不能用return返回返回值，只能用插入汇编返回结果。

naked call必须和__declspec连用，即__declspec(naked)，naked call还可以和其他调用约定联用，如：

```cpp
__declspec(naked) int __stdcall function(int a, int b)
```

使用场合：

1、_beginthread需要__cdecl的线程函数地址，_beginthreadex和CreateThread需要__stdcall的线程函数地址。

2、main函数必须是__cdecl，一般的WIN32函数和回调函数都是__stdcall，并且专门定义了宏来标识：

```cpp
   #define CALLBACK __stdcall
   #define WINAPI　 __stdcall
```

3.如果某函数在C语言编译器中编译，而在C++文件使用，由于两种编译器对函数名的解析不一样，因此需要在C++文件中使用extern "C"进行声明，否则会发生链接错误：

```cpp
   #ifdef _cplusplus
   extern "C"{
   #endif
    int func(int a, int b);
   #ifdef _cplusplus
   }
   #endif 
```

## 3. C++编译函数转换规则

C++编译时函数名的转换：?function@@YG****@Z或者?function@@YG*XZ
若函数有参数，以@Z结束；若函数无参数，则以Z结束
其中function为函数名，*代表参数表，为下列值：
      X--void ，
      D--char，
      E--unsigned char，
      F--short，
      H--int，
      I--unsigned int，
      J--long，
      K--unsigned long，
      M--float，
      N--double，
      _N--bool，
      PA--表示指针，后面的代号表明指针类型，如果相同类型的指针连续出现，以"0"代替，一个"0"代表一次重复
参数表第一项为返回类型，其后跟参数的类型，指针标识在其所指数据类型前
例：int MyFunc1(unsigned char *arg1, unsigned long arg2)
    ?MyFunc1@@YGHPAEK@Z
    void MyFunc2(char *arg1, char *arg2, char *arg3)
    ?MyFunc2@@YGXPAD00@Z
    void MyFunc3()
    ?MyFunc3@@YGXXZ
C++编译器转换函数名时更多的考虑了参数，主要是为了方便函数重载，而C语言则不存在函数重载问题

注意：对于可变参数的成员函数，始终使用__cdecl的转换方式

参考：https://www.likecs.com/show-306640430.html