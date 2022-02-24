---
title: 数字计算相关的杂题
date: 2020-12-27 23:34:03
mathjax: true
categories:
tags: 
---

## 数字相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| | [特殊的累加](./special_acc.html)  |奇技淫巧-缺乏一般性|
| | [字符串反转问题](../string_reverse.html)  |翻手法则|

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

例如输入数组[3, 32, 321]，则打印出这3个数字能排成的最小数字321323。

样例
输入：[3, 32, 321]

输出：321323
注意：输出数字的格式为字符串。

```cpp
class Solution {
public:
    
    static int compare(int a, int b) {
        string ab = to_string(a) + to_string(b);
        string ba = to_string(b) + to_string(a);
        return ab < ba;
    }
    
    string printMinNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), compare);   
        
        string res;
        for (auto x : nums) {
            res += to_string(x);
        }
        return res;
    }
};
```

请实现一个函数，把字符串中的每个空格替换成"%20"。

你可以假定输入字符串的长度最大是1000。
注意输出字符串的长度可能大于1000。

样例
输入："We are happy."

输出："We%20are%20happy."

```cpp
class Solution {
public:
    string replaceSpaces(string &str) {
        string r;
        for (auto x : str) {
            if (x != ' ') r += x;
            else r += "%20";
        }
        return r;
    }
};
```

输入一个整数 n ，求斐波那契数列的第 n 项。

假定从0开始，第0项为0。(n<=39)

样例
输入整数 n=5

返回 5

```cpp
class Solution {
public:
    int Fibonacci(int n) {
        int a = 0;
        int b = 1;
        int r = 0;
        
        while (n--) {
            r = a + b;
            a = b;
            b = r;
        }
        
        return a;
    }
};
```

数字以0123456789101112131415…的格式序列化到一个字符序列中。

在这个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数求任意位对应的数字。

样例
输入：13

输出：1

```cpp

class Solution {
public:
    int digitAtIndex(int n) {
        if(n<=9){
            return n;
        }
        int len = 1;
        long count = 9;
        int start = 1;
        while(n>len*count){
            n-=len*count;
            len+=1;
            count*=10;
            start *= 10;
        }
        start += (n-1)/len;
        string str = to_string(start);
        return str[(n-1)%len]-48;
    }
};

```

5. Pattern: Cyclic Sort，循环排序
经典题目：
Cyclic Sort (easy)
Find the Missing Number (easy)
Find all Missing Numbers (easy)
Find the Duplicate Number (easy)
Find all Duplicate Numbers (easy)







10. Pattern: Subsets，子集类型，一般都是使用多重DFS
经典题目：
Subsets (easy)
Subsets With Duplicates (easy)
Permutations (medium)
String Permutations by changing case (medium)
Balanced Parentheses (hard)
Unique Generalized Abbreviations (hard)

11. Pattern: Modified Binary Search，改造过的二分
经典题目：
Order-agnostic Binary Search (easy)
Ceiling of a Number (medium)
Next Letter (medium)
Number Range (medium)
Search in a Sorted Infinite Array (medium)
Minimum Difference Element (medium)
Bitonic Array Maximum (easy)

12. Pattern: Top ‘K’ Elements，前K个系列
经典题目：
Top ‘K’ Numbers (easy)
Kth Smallest Number (easy)
‘K’ Closest Points to the Origin (easy)
Connect Ropes (easy)
Top ‘K’ Frequent Numbers (medium)
Frequency Sort (medium)
Kth Largest Number in a Stream (medium)
‘K’ Closest Numbers (medium)
Maximum Distinct Elements (medium)
Sum of Elements (medium)
Rearrange String (hard)

13. Pattern: K-way merge，多路归并
经典题目：
Merge K Sorted Lists (medium)
Kth Smallest Number in M Sorted Lists (Medium)
Kth Smallest Number in a Sorted Matrix (Hard)
Smallest Number Range (Hard)

14. Pattern: 0/1 Knapsack (Dynamic Programming)，0/1背包类型
经典题目：
0/1 Knapsack (medium)
Equal Subset Sum Partition (medium)
Subset Sum (medium)
Minimum Subset Sum Difference (hard)

15. Pattern: Topological Sort (Graph)，拓扑排序类型
经典题目：
Topological Sort (medium)
Tasks Scheduling (medium)
Tasks Scheduling Order (medium)
All Tasks Scheduling Orders (hard)
Alien Dictionary (hard)