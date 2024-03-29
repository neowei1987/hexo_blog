---
title: 字符串
date: 2022-03-1 13:03:03
mathjax: true
categories:
- [数据结构与算法]
tags: 
- 字符串
---


### 跟字符串关联很大的数据结构包括

1. Trie
2. 后缀树
3. 后缀数组(Suffix Array)

后缀树建树的时间和空间成本都很高。**后缀数组**和后缀自动机可以看作是对后缀树时间和空间上的优化，通过映射关系避免建树和提高树节点重复利用率。

### 跟字符串相关的hash算法

- P进制hash（滚动哈希）
    1. 例如：构造哈希比较前缀和后缀，快速判断回文串

```cpp
字符串哈希 —— 模板题 AcWing 841. 字符串哈希
核心思想：将字符串看成P进制数，P的经验值是131或13331，取这两个值的冲突概率低
小技巧：取模的数用2^64，这样直接用unsigned long long存储，溢出的结果就是取模的结果

typedef unsigned long long ULL;
ULL h[N], p[N]; // h[k]存储字符串前k个字母的哈希值, p[k]存储 P^k mod 2^64

// 初始化
p[0] = 1;
for (int i = 1; i <= n; i ++ )
{
    h[i] = h[i - 1] * P + str[i];
    p[i] = p[i - 1] * P;
}

// 计算子串 str[l ~ r] 的哈希值
ULL get(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}
```

### 跟字符串有关系的技巧

1. 翻手定则

```cpp
class Solution {
public:
    void reverse(string& s, int i, int j) {
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }

    string trans(string s, int n) {
        int begin = 0;
        for (int i = 0; i < s.length();) {
            if (s[i] == ' ') {
                reverse(s, begin, i - 1);
                i++;
                begin = i;
            }
            else {
                i++;
            }
        }
        reverse(s, begin, s.length() - 1);

        reverse(s, 0, s.length() - 1);

         for (int i = 0; i < s.length(); ++i) {
             if (s[i] >= 'a' && s[i] <= 'z') {
                 s[i] = 'A' + (s[i] - 'a');
             } else if (s[i] >= 'A' && s[i] <= 'Z') {
                 s[i] = 'a' + (s[i] - 'A');
             }  
         }
        return s;
    }
};
```

### 字符串匹配算法
