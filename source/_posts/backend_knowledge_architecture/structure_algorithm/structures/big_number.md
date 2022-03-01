---
title: 大数高精度加减乘除
date: 2022-03-01 21:10:03
updated:
copyright: true
password:
keywords: 
description: 
mathjax: true
categories:
tags: 
---

一般而言，通过倒序vector\<int>来表示高精度大数；

因为做运算时，通常需要从低位开始，所以一般vector需要进行逆转处理。

```cpp
//高精度加法 —— 模板题 AcWing 791. 高精度加法
// C = A + B, A >= 0, B >= 0
vector<int> add(vector<int> &A, vector<int> &B)
{
    if (A.size() < B.size()) return add(B, A);

    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i ++ )
    {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }

    if (t) C.push_back(t);
    return C;
}

//高精度减法 —— 模板题 AcWing 792. 高精度减法
// C = A - B, 满足A >= B, A >= 0, B >= 0
vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i ++ )
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }

    //清除后面的0（高位）
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

//高精度乘低精度 —— 模板题 AcWing 793. 高精度乘法
// C = A * b, A >= 0, b > 0
vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size() || t; i ++ )
    {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    return C;
}

//高精度除以低精度 —— 模板题 AcWing 794. 高精度除法
// A / b = C ... r, A >= 0, b > 0
vector<int> div(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i -- )
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
```
