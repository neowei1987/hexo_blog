---
title: 回溯系列-组合排列
date: 2021-1-2 16:29:03
mathjax: true
categories:
tags: 
---


给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

### N选K组合解题思路

状态：第i个

选择: n-i个选择

路径：path选择

结果集：列表

结束条件： 找到所有的组合； path路径到了k

```cpp

vector<int> path;
void dfs(int u, int start_idx) {
    if (u == k) {
        //path
        return;
    }

    //未剪枝版
    for (int i = start_idx; i <= n; ++i) {
        path.push_back(i);
        dfs(u + 1, i + 1) ; //注意i+1
        path.pop_back();
    }

    //带剪枝版(如果i过大的话，剩下的元素会不足k个)
    for (int i = start_idx; i <= n - (k - path.size()); ++i) {
        path.push_back(i);
        dfs(u + 1, i + 1);
        path.pop_back();
    }

}

dfs(0, 0);
```

找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

### N选K组合的和解题思路

状态：第i个

选择: 9-i个选择

路径：path选择

结果集：列表

结束条件： 找到所有的组合； path路径到了k，sum ok

```cpp

vector<int> path;
void dfs(int u, int sum, int start) {
    if (sum > n) {return;}
    if (u == k) {
        if (sum == 0) {
            res.push_back(path);
        }
        return;
    }

    for (int i = start; i <= 9 - (k - path.size()) + 1; i++) {
        path.push_back(i);
        dfs(u + 1, sum - i, i + 1);
        path.pop_back();
    }
}

dfs(0, n, 0);
```

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。

解集不能包含重复的组合。

### candidates找和为target解题思路

状态：第i个

选择: 每次都有N个选择

路径：path选择

结果集：列表

结束条件： 找到所有的组合； path路径到了k，sum ok

```cpp
    //如果是一个集合来求组合的话，就需要startIndex
    void dfs(vector<int>& d, int u, int sum, int start) {
        if (sum > target) {return;}
        if (sum == target) {
            res.push_back(path);
            return;
        }

        for (int i = start; i < n; ++i) {
            path.push_back(d[i]);
            dfs(d, u + 1, sum + d[i], i); //可以重复使用,
            path.pop_back();
        }
    }

    //剪枝优化： 排序(从大到小排序），提前终止，判定条件
    void dfs(vector<int>& d, int u, int sum, int start) {
        if (sum > target) {return;}
        if (sum == target) {
            res.push_back(path);
            return;
        }

        //排序后，可以剪枝，提前终止本层（因为后面的更小了，只要i不可以，后面的更不可以，可以提前终止）
        for (int i = start; i < n && sum+d[i] <= target; ++i) {
            path.push_back(d[i]);
            dfs(d, u + 1, sum + d[i], i); //可以重复使用
            path.pop_back();
        }
    }
```

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。 
说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。

//需要进行排序预处理，从大到小

```cpp
void dfs(vector<int>& d, int u, int sum, int start_index) {
        if (sum > target) {return;}
        if (sum == target) {
            res.push_back(path);
            return;
        }

        for (int i = start_index; i < n && sum + d[i] <= target; ++i) {
            //在同一层次上，相同的元素不重复选取（因为前面的已经处理过了）
            if (i >= 1 && d[i] == d[i - 1] && used[i - 1] == false) {continue;}
            path.push_back(d[i]);
            used[i] = true;
            dfs(d, u + 1, sum + d[i], i + 1);
            used[i] = false;
            path.pop_back();
        }
    }
```

给定一个 没有重复 数字的序列，返回其所有可能的全排列。

//给坑选元素。

```cpp
    void dfs(vector<int>& d, int u) {
        if (u == n) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < n; ++i ) {
            if (used[i]) continue;
            path.push_back(d[i]);
            used[i] = true;
            dfs(d, u + 1);
            used[i] =false;
            path.pop_back();
        }
    }
```

//给元素选坑，后面可以选择的坑原来越少了。
//u代表哪一个元素。

```cpp
    void dfs(vector<int>& d, int u) {
        if (u == n) {
            res.push_back(d);
            return;
        }

        for (int i = u; i < n; ++i ) {
            swap(d[u], d[i]);
            dfs(d, u + 1);
            swap(d[u], d[i]);
        }
    }

```

输入一组数字（可能包含重复数字），输出其所有的排列方式。

样例
输入：[1,2,3]

输出：
      [
        [1,2,3],
        [1,3,2],
        [2,1,3],
        [2,3,1],
        [3,1,2],
        [3,2,1]
      ]

下面这种方式是特定元素选择坑位

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    
    void dfs(vector<int>& nums, int u, int start, int state) {
        if (u == int(nums.size())) {
            res.push_back(path);
            return;
        }
        
        //对于重复元素，则放在前面的元素后面；否则从0开始
        if (!u || nums[u] != nums[u - 1]) start = 0;
                
        for (int i = start; i < nums.size(); ++i) {
            if (!(state >> i & 1)) {
                //这一步骤是关键，为第u号元素找可以选择的坑位
                path[i]= nums[u];
                dfs(nums, u + 1, i + 1, state + (1 << i));
            }
        }
    }
    
    vector<vector<int>> permutation(vector<int>& nums) {
        path.resize(nums.size());
        sort(nums.begin(), nums.end());
        dfs(nums, 0, 0, 0);
        return res;
    }
};
```

为坑选择合适的元素，排个序先。

```cpp
    void dfs(int u) {
        if (u == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 &&  nums[i] == nums[i - 1] && !used[i - 1]) continue;
            if (used[i]) continue;
            used[i] = true;
            //为新的坑，选择了一个新的元素
            path.push_back(nums[i]);
            dfs(u + 1);
            path.pop_back();
            used[i] = false;
        }
    }
```

给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

示例:

输入: [4, 6, 7, 7] 输出: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]

说明:

给定数组的长度不会超过15。
数组中的整数范围是 [-100,100]。
给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况。

```cpp
 void dfs(int u, int start) {
        if (u >= 2) {
            res.push_back(path);
        }

        unordered_set<int> iset;
        for (int i = start; i < d.size(); i++) {
            if (iset.count(d[i])) continue;
            if (path.size() && path.back() > d[i]) continue;

            iset.insert(d[i]);
            path.push_back(d[i]);
            dfs(u + 1, i + 1);
            path.pop_back();
        }
    }
```

https://zhuanlan.zhihu.com/p/339849416