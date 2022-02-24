---
title: 内存池系列｜nginx内存分配
---

![nginx内存池](https://gimg2.baidu.com/image_search/src=http%3A%2F%2Fimg.it610.com%2Fimage%2Finfo5%2F7488f6235cda4dabaa7beed536bac0ba.jpg&refer=http%3A%2F%2Fimg.it610.com&app=2002&size=f9999,10000&q=a80&n=0&g=0n&fmt=jpeg)

有几个：

1. nginx_pool_s 虽然包含了 ngx_pool_data，但是nginx_pool_s本身的内存管理还是通过ngx_pool_data来进行分配的
2. 可以理解为：nginx_pool_s是一种特殊类型的ngx_pool_data。
3. nginx_pool_s 维护了current指针，来指向下一个用来分配内存的小内存块链表节点
4. nginx_pool_s 维护了large指针，来指向下一个用来分配内存的d大内存块链表节点
5. ngx_pool_data 维护了next指针 来指向下一个nginx_pool_s
