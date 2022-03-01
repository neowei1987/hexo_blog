---
title: Trie系列 - 概览
date: 2022-03-1 13:08:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- Trie
---


字典树(Trie)，顾名思义是以树结构来模拟字典。

回想我们查字典的过程，比如查找"man"，先翻到字典m部分，再翻第二个字母a和第三个字母n，一共查找3次。

查找次数最多是等于个单词的长度。插入查找单词的时间复杂度时$O(m)$，此外有公共前缀的单词只需存一次公共前缀，节省了空间，也可理解为**前缀树**。

#### 字典树应用

- 字符串检索
    1. 查询检索字符串
- 词频统计
    1. 统计一个单词出现了多少次
- 字符串排序
    1. 字典树建好后，先序遍历就得到了排序。
- 前缀匹配
    1. 根据前缀，用于搜索提示等

```cpp
int son[N][26], cnt[N], idx;
// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以每个节点结尾的单词数量

// 插入一个字符串
void insert(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++ ;
}

// 查询字符串出现的次数
int query(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}
```
