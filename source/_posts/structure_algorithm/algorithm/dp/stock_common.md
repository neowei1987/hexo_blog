---
title: 股票买卖系列-通用解法
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
categories:
- [数据结构与算法]
tags: 
---

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

```cpp
class Solution {
public:
    const int inf = 0x3f3f3f3f;
    int dp[100010][3][2];

    int maxProfit(vector<int>& prices) {
        //状态机dp
        //阶段
        int n = prices.size();
        int k = 2;
        //base
        for (int k = 0; k <= 2; k++) {
            dp[0][k][0] = 0;
            dp[0][k][1] = -inf;
        }

        for (int i = 0; i <= n; ++i) {
            dp[i][0][0] = 0;
            dp[i][0][1] = -inf;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= 2; k++) {
                              //前一天没有股票；昨天有股票，今天卖出；
                dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
                                //前一天有股票；昨天没有股票，今天买入
                dp[i][k][1] =  max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]); 
            }
        }

        return dp[n][2][0];
    }
};
```
