---
title: 贪心算法-区间问题
date: 2020-12-28 21:53:03
mathjax: true
categories:
- 数据结构与算法
tags: 
- 贪心
---

## 区间大类的常见套路

猜出一般步骤

1. 对区间进行排序（按照左端点、右端点）
2. 挨个对区间进行进行枚举，选择局部最优解

证明选择的策略是否是正确的

## 经典题目

### 区间选点问题

问题描述：给定N个区间[a,b]，取尽量少的点，使得每个区间内都至少有一个点（不同区间内含的点可以重复）
解法：

1. 按照右端点排序

2. 枚举区间，选择区间的右端点作为候选集（显然最右边是局部最优解）

```cpp

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d%d", &range[i].l, &range[i].r);

    sort(range, range + n);

    int res = 0, ed = -2e9;
    for (int i = 0; i < n; i ++ )
        if (ed < range[i].l)
        {
            res ++ ;
            ed = range[i].r;
        }

    printf("%d\n", res);

    return 0;
}

```

### 最大不相交区间数量

类似于选课，课程有交集，我们需要选择最多的课程，使得课程之间没有时间冲突。

1. 按照右端点排序

2. 枚举区间，选择区间的右端点作为候选集（显然最右边是局部最优解）

如果我多选择一个区间，就会出现相交；

```cpp
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>eg[i].l>>eg[i].r;

    }
    sort(eg, eg+n);
    int res=0, ed=-2e9;
    for(int i=0;i<n;i++){
        if(ed<eg[i].l) {
            res++, ed=eg[i].r;
        }else{

        }
    }
    cout<<res;
}
```

### 区间分组

给定N个闭区间，请你将这些区间分成若干组，使得每组内部的区间两两之间（包括端点）没有交集，并使得组数尽可能小。 输出最小组数。

排序 + 利用**小根堆**来动态维护最大值（max_r)

top()返回最小的最大值，既然最小的都有交集，更大的就更不用说啦。

1. 按照左边排序
2. 枚举区间，能否将该区间加入到当前分组中（L[i] > Max_r）
   1. 如果不存在这样子的组，则开新组
   2. 加入到当前组中，更新max_r

```cpp

bool cmd(const PII& a, const PII& b) {
    return a.first < b.first;
}

sort(a, a+n, cmp);

priority_queue<int, vector<int>, greater<int>> q;

q.push(a[0].second);
for (int i = 1; i < n; ++i) {
    int ed = q.top();
    if (a[i].first > ed) {
        q.pop(); //先pop，再push，相当于更新了该分组的max_r
    }
    q.push(a[i].second);
}

return q.size();

```

### 区间覆盖

给定 N 个闭区间 [ai,bi] 以及一个线段区间 [s,t]，请你选择尽量少的区间，将指定线段区间完全覆盖。

输出最少区间数，如果无法完全覆盖则输出 −1。

1. 左端点从小到大排序
2. 从前往后依次枚举每个区间，在所有能覆盖start的区间中，选择右端点最大的区间，然后将start更新为右端点的最大值。


```cpp
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

typedef pair<int, int> PII;

const int N = 1e5 + 10;
PII a[N];

bool cmp(const PII& a, const PII& b) {
    return a.first < b.first;
}

int main() {
    int res = 0, i = 0;
    bool success = false;
    for (i = 0; i < n; ) {
        int max_r = -INF;
        while (i < n && a[i].first <= lr) {
            max_r = max(max_r, a[i].second);
            i++;
        }
        
        if (max_r == -INF) { //没有找到任何能够覆盖start的区间
            res = -1;
            break;
        }
        
        res++;
        if (max_r >= rr) {
            success = true;
            break;
        } 
        lr = max_r;
    }
    
    if (!success) res = -1;
}
```

### 合并区间

1. 首先对区间按照起始端点（左断点）进行升序排序，
2. 然后逐个判断当前区间是否与前一个区间重叠，如果不重叠的话将当前区间直接加入结果集，反之如果重叠的话，就将当前区间与前一个区间进行合并。

```cpp
typedef pair<int, int> PII;
const int inf = 0x3f3f3f3f;
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<PII> d(intervals.size());
        vector<vector<int>> res;
        int n = intervals.size();
        for (int i = 0; i < n; ++i) {
            d[i].first = intervals[i][0];
            d[i].second = intervals[i][1];
        }
        sort(d.begin(), d.end());
        int st = 0, ed = -inf;
        for (int i = 0; i < n; ++i) {
            if (d[i].first > ed) {
                if (ed != -inf) {
                    vector<int> t = {st, ed};
                    res.push_back(t);
                } 
                //把当前区间扩充一下
                st = d[i].first, ed = d[i].second;
            }
            else {
                ed = max(ed, d[i].second);
            }
        }

        vector<int> t = {st, max(ed, d.back().second)};
        res.push_back(t);

        return res;
    }
};
```
