---
title: 股票买卖问题-限定两次
date: 2022-12-01 13:03:03
updated:
description: 
mathjax: true
categories:
tags: [动态规划]
---

假设你有一个数组prices，长度为n，其中prices[i]是某只股票在第i天的价格，请根据这个价格数组，返回买卖股票能获得的最大收益
1. 你最多可以对该股票有两笔交易操作，一笔交易代表着一次买入与一次卖出，但是再次购买前必须卖出之前的股票
2. 如果不能获取收益，请返回0
3. 假设买入卖出均无手续费

<!-- more -->

```cpp

const int N = 1e5 + 1;
//dp[i][k][0]; 第i天时，当前空仓，不持有股票，可交易次数
//dp[i][k][1]，第i天时，当前满仓，持有股票，，可交易次数
int dp[N][3][2];

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 两次交易所能获得的最大收益
     * @param prices int整型vector 股票每一天的价格
     * @return int整型
     */
    int maxProfit(vector<int>& prices) {
        //状态，选择
        /*
        for (int i = 0; i < prices.size(); ++i) {
            dp[i][0][0] = 0;
            dp[i][0][1] = INT32_MIN;
        }*/
        //第-1天，不持仓 == 0
        //第-1天，持仓 === -INF
        //第i天，0交易次数，0 = 0
        //第i天，0交易次数，1 = -INF

        for (int i = 0; i < prices.size(); ++i) {
            for (int k = 2; k >= 1; k--) {
                if (i == 0) {
                    dp[i][k][1] = -prices[i]; /* dp[i - 1][k-1][0] - prices[i] 前半部分等于0*/
                    dp[i][k][0] = 0;
                    continue;
                }

                //对于持仓状态，由前一天的买入状态、前一天的rest变化而来；
                dp[i][k][1] = max(
                    dp[i - 1][k-1][0] - prices[i], //选择买入
                    dp[i - 1][k][1]               //保持不变
                );
                //对于空仓状态，由前一天的卖出状态、前一天的rest变化而来；
                dp[i][k][0] = max(
                    dp[i - 1][k][1] + prices[i],  //选择卖出
                    dp[i - 1][k][0]
                );
            }
        }

        return dp[prices.size() - 1][2][0];
    }
};
```