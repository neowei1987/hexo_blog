---
title: 操作系统系列｜虚拟内存
date: 2022-02-25 10:55:03
updated:
mathjax: true
categories:
tags: 
- 操作系统
---

![虚拟地址转换为物理地址的本质](https://pics7.baidu.com/feed/95eef01f3a292df5ed263835cecf2b6835a8732b.png?token=d3599f2975744c1d572bd6e62b2daf04)

我们知道linux采用了分页机制，通常采用四级页表，页全局目录(PGD)，页上级目录(PUD)，页中间目录(PMD)，页表(PTE)。如下：

![虚拟地址转换为物理地址硬件过程](https://pics2.baidu.com/feed/728da9773912b31b18d3813af7e64172dbb4e169.png?token=c455dcb1766f6df26c45bc14d987b355)

1. 从CR3寄存器中读取页目录所在物理页面的基址(即所谓的页目录基址)，从线性地址的第一部分获取页目录项的索引，两者相加得到页目录项的物理地址。
2. 第一次读取内存得到pgd_t结构的目录项，从中取出物理页基址取出，即页上级页目录的物理基地址。
3. 从线性地址的第二部分中取出页上级目录项的索引，与页上级目录基地址相加得到页上级目录项的物理地址。
4. 第二次读取内存得到pud_t结构的目录项，从中取出页中间目录的物理基地址。
5. 从线性地址的第三部分中取出页中间目录项的索引，与页中间目录基址相加得到页中间目录项的物理地址。
6. 第三次读取内存得到pmd_t结构的目录项，从中取出页表的物理基地址。
7. 从线性地址的第四部分中取出页表项的索引，与页表基址相加得到页表项的物理地址。
8. 第四次读取内存得到pte_t结构的目录项，从中取出物理页的基地址。
9. 从线性地址的第五部分中取出物理页内偏移量，与物理页基址相加得到最终的物理地址。
10. 第五次读取内存得到最终要访问的数据。

整个过程是比较机械的，每次转换先获取物理页基地址，再从线性地址中获取索引，合成物理地址后再访问内存。不管是页表还是要访问的数据都是以页为单位存放在主存中的，因此每次访问内存时都要先获得基址，再通过索引(或偏移)在页内访问数据，因此可以将线性地址看作是若干个索引的集合。

### 虚拟内存管理

#### Linux通过红黑树管理

```cpp
struct task_struct {

    struct mm_struct *mm;

}

struct vm_area_struct {
    struct mm_struct * vm_mm;    /* 所属的内存描述符 */
    unsigned long vm_start;    /* vma的起始地址 */
    unsigned long vm_end;        /* vma的结束地址 */
 
    /* 该vma的在一个进程的vma链表中的前驱vma和后驱vma指针，链表中的vma都是按地址来排序的*/
    struct vm_area_struct *vm_next, *vm_prev;
 
    pgprot_t vm_page_prot;        /* vma的访问权限 */
    unsigned long vm_flags;    /* 标识集 */
 
    struct rb_node vm_rb;      /* 红黑树中对应的节点 */
}
```

该结构体是一段虚拟内存，从vm_start到vm_end，他们拥有相同的权限；
vm_prev 、vm_next 是双向链表的next与pre；
vm_rb 是红黑树节点

```cpp
struct mm_struct {
        struct vm_area_struct * mmap;       /* list of VMAs */
        struct rb_root mm_rb;/*又是红黑树的根节点*/
        struct vm_area_struct * mmap_cache;      /* last find_vma result */
}
```

mmap是双向链表；按照地址大小来顺序管理所有的area

mm_rb是红黑树的根节点

红黑树的Key-Value: 虚拟地址区间 => 对应的area.
