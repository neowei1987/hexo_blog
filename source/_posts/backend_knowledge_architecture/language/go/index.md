---
title: go语言陷阱
date: 2022-12-013 22:03:03
updated:
description: 
mathjax: true
categories:
tags: [编程语言]
---

### 变量&类型相关

```go

func main() {
    var a = []interface{}{1, 2, 3}

    //变参函数忘记...展开
    fmt.Println(a)
    fmt.Println(a...)
} 

func main() {
    x := [3]int{1, 2, 3}

    //在函数调用参数中，数组是值传递，无法通过修改数组类型的参数返回结果。
    func(arr [3]int) {
        arr[0] = 7
        fmt.Println(arr)
    }(x)

    fmt.Println(x)
}


func Foo() (err error) {
    if err := Bar(); err != nil {
        return
    }
    return
}

//map是一种hash表实现，每次遍历的顺序都可能不一样。
func main() {
    m := map[string]string{
        "1": "1",
        "2": "2",
        "3": "3",
    }

    for k, v := range m {
        println(k, v)
    }
}

```

<!-- more -->

### 调度相关

GMP模型-GoRoutine, Machine, Processor

G（Goroutine）：代表Go 协程Goroutine，存储了 Goroutine 的执行栈信息、Goroutine 状态以及 Goroutine 的任务函数等。G的数量无限制，理论上只受内存的影响，创建一个 G 的初始栈大小为2-4K，配置一般的机器也能简简单单开启数十万个 Goroutine ，而且Go语言在 G 退出的时候还会把 G 清理之后放到 P 本地或者全局的闲置列表 gFree 中以便复用。

M（Machine）： Go 对操作系统线程（OS thread）的封装，可以看作操作系统内核线程，想要在 CPU 上执行代码必须有线程，通过系统调用 clone 创建。M在绑定有效的 P 后，进入一个调度循环，而调度循环的机制大致是从 P 的本地运行队列以及全局队列中获取 G，切换到 G 的执行栈上并执行 G 的函数，调用 goexit 做清理工作并回到 M，如此反复。M 并不保留 G 状态，这是 G 可以跨 M 调度的基础。M的数量有限制，默认数量限制是 10000，可以通过 debug.SetMaxThreads() 方法进行设置，如果有M空闲，那么就会回收或者睡眠。

P（Processor）：虚拟处理器，M执行G所需要的资源和上下文，只有将 P 和 M 绑定，才能让 P 的 runq 中的 G 真正运行起来。P 的数量决定了系统内最大可并行的 G 的数量，**P的数量受本机的CPU核数影响，可通过环境变量$GOMAXPROCS或在runtime.GOMAXPROCS()来设置，默认为CPU核心数。

#### 基于信号的抢占式调度

真正的抢占式调度是基于信号完成的，所以也称为“异步抢占”。不管协程有没有意愿主动让出 cpu 运行权，只要某个协程执行时间过长，就会发送信号强行夺取 cpu 运行权。

M 注册一个 SIGURG 信号的处理函数：sighandler
sysmon启动后会间隔性的进行监控，最长间隔10ms，最短间隔20us。如果发现某协程独占P超过10ms，会给M发送抢占信号
M 收到信号后，内核执行 sighandler 函数把当前协程的状态从_Grunning正在执行改成 _Grunnable可执行，把抢占的协程放到全局队列里，M继续寻找其他 goroutine 来运行
被抢占的 G 再次调度过来执行时，会继续原来的执行流

```go
//Goroutine是协作式抢占调度，Goroutine本身不会主动放弃CPU：
//解决的方法是在for循环加入runtime.Gosched()调度函数：或者是通过阻塞的方式避免CPU占用：

func main() {
    runtime.GOMAXPROCS(1)

    go func() {
        for i := 0; i < 10; i++ {
            fmt.Println(i)
        }
    }()


    for {
        runtime.Gosched()
    }

    select{}
}
```

### 闭包相关

```go

//闭包错误引用同一个变量
func main() {
    for i := 0; i < 5; i++ {
        defer func() {
            //打印的i往往会不符合预期
            println(i)
        }()
    }
}

//改进的方法是在每轮迭代中生成一个局部变量：
func main() {
    for i := 0; i < 5; i++ {
        i := i
        defer func() {
            println(i)
        }()
    }
}

 //或者是通过函数参数传入：
func main() {
    for i := 0; i < 5; i++ {
        defer func(i int) {
            println(i)
        }(i)
    }
}

```

### defer相关

```go

//defer在函数退出时才能执行，在for执行defer会导致资源延迟释放：
func main() {
    for i := 0; i < 5; i++ {
        f, err := os.Open("/path/to/file")
        if err != nil {
            log.Fatal(err)
        }
        defer f.Close()
    }
}

//解决的方法可以在for中构造一个局部函数，在局部函数内部执行defer：
func main() {
    for i := 0; i < 5; i++ {
        func() {
            f, err := os.Open("/path/to/file")
            if err != nil {
                log.Fatal(err)
            }
            defer f.Close()
        }()
    }
}
```

### error判定相关

```go

//比如返回了一个错误指针，但是并不是空的error接口：
type MyError struct {
   code int
   msg  string
}

func (e *MyError) Error() string {
   return fmt.Sprintf("code:%d,msg:%v", e.code, e.msg)
}

func returnsError() error {
    var p *MyError = nil
    if bad() {
        p = ErrBad
    }

    //因为error是一个interface
    //interface分为两部分：type + value
    //返回的p是(*MyError, nil)
    //这个玩意并不是单纯意义的nil
    return p // Will always return a non-nil error.
}
```

### 切片相关

slice底层结构并没有使用加锁等方式，不支持并发读写，所以并不是线程安全的，使用多个 goroutine 对类型为 slice 的变量进行操作，每次输出的值大概率都不会一样，与预期值不一致; slice在并发执行中不会报错，但是数据会丢失

切片append时，会发生变化

```go
//切片会导致整个底层数组被锁定，底层数组无法释放内存。如果底层数组较大会对内存产生很大的压力。
func main() {
    headerMap := make(map[string][]byte)

    for i := 0; i < 5; i++ {
        name := "/path/to/file"
        data, err := ioutil.ReadFile(name)
        if err != nil {
            log.Fatal(err)
        }
        //解决的方法是将结果克隆一份，这样可以释放底层的数组：
        headerMap[name] = append([]byte{}, data[:1]...)
        headerMap[name] = data[:1]
    }

    // do some thing
}

```

### 多线程相关

map、slice等线程不安全

```go

//不同Goroutine之间不满足顺序一致性内存模型

var msg string
var done bool

func setup() {
    msg = "hello, world"
    done = true
}

func main() {
    go setup()
    //这个done可能已经加载到CPU cache中了，并不会每次读主存寸
    for !done {
    }
    println(msg)
}

//因为在不同的Goroutine，main函数中无法保证能打印出hello,world:

//下文为正确解法
var msg string
var done = make(chan bool)

func setup() {
    msg = "hello, world"
    done <- true
}

func main() {
    go setup()
    <-done
    println(msg)
}
```

### recover相关

```go

//在局部作用域中，命名的返回值内同名的局部变量屏蔽：
func Foo() (err error) {
    if err := Bar(); err != nil {
        return
    }
    return
}

//必须在defer函数中直接调用才有效：多层嵌套依然无效、直接defer调用也是无效
func main() {
    defer func() {
        recover()
    }()
    panic(1)
}
```

### 内存相关

逃逸机制

编译器会根据变量是否被外部引用来决定是否逃逸：
如果函数外部没有引用，则优先放到栈中；
如果函数外部存在引用，则必定放到堆中;
如果栈上放不下，则必定放到堆上;

总结

栈上分配内存比在堆中分配内存效率更高
栈上分配的内存不需要 GC 处理，而堆需要
逃逸分析目的是决定内分配地址是栈还是堆
逃逸分析在编译阶段完成

### goroutine

协程是用户态轻量级线程，它是线程调度的基本单位。通常在函数前加上go关键字就能实现并发。一个Goroutine会以一个很小的栈启动2KB或4KB，当遇到栈空间不足时，栈会**自动伸缩**， 因此可以轻易实现成千上万个goroutine同时启动。

#### goroutine泄漏

泄露原因

1. Goroutine 内进行channel/mutex 等读写操作被一直阻塞。
2. Goroutine 内的业务逻辑进入死循环，资源一直无法释放。
3. Goroutine 内的业务逻辑进入长时间等待，有不断新增的 Goroutine 进入等待

```go
func main() {
    ch := func() <-chan int {
        ch := make(chan int)
        //这个协程一直pending在write channel上
        go func() {
            for i := 0; ; i++ {
                ch <- i
            }
        } ()
        return ch
    }()

    for v := range ch {
        fmt.Println(v)
        if v == 5 {
            break
        }
    }
}

func main() {
    ctx, cancel := context.WithCancel(context.Background())

    ch := func(ctx context.Context) <-chan int {
        ch := make(chan int)
        go func() {
            for i := 0; ; i++ {
                select {
                case <- ctx.Done(): 
                    return
                case ch <- i:
                }
            }
        } ()
        return ch
    }(ctx)

    for v := range ch {
        fmt.Println(v)
        if v == 5 {
            cancel()//ctx会done掉
            break
        }
    }
}
```

golang gc 简明过程

参考：
https://zhuanlan.zhihu.com/p/92210761