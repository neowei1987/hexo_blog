一个基本的CPU执行计算的过程如下：
1. 程序以及数据被加载到主内存
2. 指令和数据被加载到CPU的高速缓存
3. CPU执行指令，把结果写到高速缓存
4. 高速缓存中的数据写回主内存

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

## 函数调用

ESP越来愈小
ESP比EBP小

一个函数

1. 参数压入stack中 
    push p1
    push p2
2. CPU把返回地址压入stack中
    push eip
3. 跳转到新的函数地址(call func)，开始执行
    push ebp 保存老函数的EBP到新的stack中
    mov esp => ebp  让ebp保存新函数的stack base
4. 分配局部变量
    sub esp 100 分配100字节的局部变量
5. 局部变量赋值与访问
    通过ebp - XX 来访问局部变量
6. 访问参数
    通过ebp + xxx 来访问参数
7. 函数返回
    add esp 100
    mov ebp => esp 
    pop ebp 还原ebp
    ret（pop eip）
8. 将压入的参数POP出来
    pop p2
    pop p1

## co 实现

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
 
具体参考：https://vinsflyfish.github.io/posts/thinking-in-libco/