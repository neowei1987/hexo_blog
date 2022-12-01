---
title: 回溯-序列切分
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
---

给定数字N和M，你需要从数字1到N的序列中添加+或-，使得序列的和等于M。

打印出所有满足此关系的序列，例如，给定N=4 M=6,则满足条件得序列是1-2+3+4=6(一定存在此序列)

```cpp

void dfs(int u) {
    //剪枝，如果当前明确的sum已经超了，则直接return
    if (exceed_already()) {
        return false;
    }

    if (u == n) {
        //check 是否满足
        //cmd存了切割位置，我们按照cmd寸的切割位置，把字符串切割出来，转为整数，然后求和
        return true;
    }

    //分割
    cmd[u] = 1;
    if (dfs(u + 1)) {
        return true;
    }
    
    //不分割
    cmd[u] = 0;
    return dfs(u + 1);
}

```