---
title: 动态规划分类索引
date: 2021-01-11 22:54:03
updated:
copyright: true
description: 
mathjax: true
categories:
- 数据结构与算法
tags: 
- 动态规划
---
### DP概念

动态规划是运筹学的一个分支，是一种求解多阶段决策过程最优化问题的数学方法。要搞清楚它，首先需要搞清楚几个基本概念。

阶段：整个决策过程可以按某个（空间、时间或其它）标准分为多个步骤，每一步称为一个阶段。比如下棋，走一步就可以认为是一个阶段。

状态：状态表示在每个阶段我们关注的决策相关的影响因素的情况。比如下棋到某一步时，此刻棋盘上所有棋子的位置就是此阶段的状态。状态通常可以用一个或多个变量来描述。

决策：一个阶段的状态给定以后，从该状态演变到下一阶段某个状态的一种选择行动方法称为决策。比如下棋到某一步时，决定下一步怎么走，就是一步决策，也叫单阶段决策。决策通常也可以用变量来描述。

策略：由每个阶段的决策组成的序列称为策略，也就是多阶段决策。比如下棋，从开始下到结束的每一步走法构成了一个策略。策略可能有很多种，其中达到最优效果的策略称为最优策略。

状态转移方程：从一个阶段到下一个阶段的状态变化，称为状态转移，如果这个变化可以用方程来描述，则称之为状态转移方程。

无后效性：说的是一旦某个阶段的状态确定，则此后过程的演变不再受此前各种状态及决策的影响。也就是说历史信息不会影响我们以后的决策。比如下棋，现在已经有一个棋面，有可能是随机摆成的，也可能是认真下成这样的，但是不管怎样这不影响我们去决定下一步应该怎么下。当前的棋面是唯一影响未来的东西。

最优⼦结构：如果每个阶段的最优状态可以从之前某个或某些阶段的某个或某些状态直接得到，也就是说一个问题的最优解可以由其子问题的最优解来得到，我们称其具有最优子结构。

重叠⼦问题：在求解一个问题时需要先求解其子问题，子问题又有子问题，若在求解过程中需要重复求解某些子问题，这些子问题称为重叠子问题。对于重叠子问题不需要重复求解，只需要求解一次，然后记录下来，以后每次查询就可以了，可以大大降低运行时间，即用空间换时间。

参考：https://blog.csdn.net/tyst08/article/details/106412008

简单起见，下面用大家非常熟悉的求斐波拉契数列的过程来说明这几个概念。斐波拉契数列的公式为：

f(1)=f(2)=1

f(n)=f(n−1)+f(n−2)(n≥3)

假设我现在想计算第10个非波那契数，那么计算每一个斐波拉契数的过程就是一个阶段，每一个斐波拉契数就是这个问题的一个状态。按照公式计算就是决策。每一步都按公式算就是策略。状态转移方程为 f ( n ) = f ( n − 1 ) + f ( n − 2 ) f(n) = f(n-1) + f(n-2)f(n)=f(n−1)+f(n−2)。求一个新数字只需要之前的两个状态，与怎么得到这个状态值无关，所以具有无后效性。每个阶段的状态即斐波拉契数可以由之前的两个状态得到，所以具有最优子结构。根据公式，求 f ( n ) f(n)f(n) 时需要求 f ( n − 2 ) f(n-2)f(n−2)，求 f ( n − 1 ) f(n-1)f(n−1) 时也需要求 f ( n − 2 ) f(n-2)f(n−2)，所以有重叠⼦问题。

动态规划就是利用最优子结构，把**多阶段决策过程的最优化问题**转化为一系列**单阶段最优化问题**，然后逐个求解子问题。在每一个子问题的求解中，均可以利用了它前面的子问题的最优化结果，依次进行，直到得到最后一个子问题的最优解，也就是整个问题的最优解。

动态规划的流程一般可以分为以下几步：

1. 对决策过程划分阶段。
2. 对各阶段确定状态变量。
3. 根据状态变量确定每个决策的开销以及最终的目标函数。
4. 建立各阶段状态变量的转移过程，确定状态转移方程。
5. 根据状态转移方程用代码来实现，一般可以用递归，注意对重叠子问题要记录其解。

### 动态规划优化策略

1. 费用提前/延后计算：没有关于某个维度的限制条件，这个维度纯粹用来计算费用，考虑是否可以提前计算
2. 空间压缩

### 经典问题

常见的动态规划问题有哪些：

|  打家劫舍（普通版本）  | |
|  ----  | ----  |
| 问题描述   |不能打结连续的两家人|
| 状态表示  |F[i]表示前 i 间房屋能偷窃到的最高总金额|
| 阶段划分 | 空间特征，子序列的结尾位置（数列A中的位置，从前到后） |
| 转移方程  |$F[i]=max(F[i-1], F[i-2]+A[i])$|
| 边界  | F[0]= 0|
| 目标  | $F[N]$|
| 优化点  | 只跟前2有关系，滚动数组|
| 相关题目  |  |

|  打家劫舍（环形数组）  | |
|  ----  | ----  |
| 问题描述   |不能打结连续的两家人|
| 状态表示  |F[i]表示前 i 间房屋能偷窃到的最高总金额|
| 阶段划分 | 空间特征，子序列的结尾位置（数列A中的位置，从前到后） |
| 转移方程  |$F[i]=max(F[i-1], F[i-2]+A[i])$|
| 边界  | F[0]= 0|
| 目标  | $F[N]$|
| 优化点  | 连续两次普通版本，分别是打结第一家 OR 不打结第一家|
| 相关题目  |  |

|  打家劫舍（二叉树版本）  | |
|  ----  | ----  |
| 问题描述   | |
| 状态表示  |dp[HASH_KEY] = MONEY|
| 阶段划分 |  |
| 转移方程  ||
| 边界  | |
| 目标  |二叉树遍历 + 记忆化搜索加速|
| 相关题目  |  |

|  LIS（Longest Increasing Subsequence）问题  | |
|  ----  | ----  |
| 问题描述   | 最长上升子序列。给定一个长度为N的数列A，求数值单调递增的子序列的长度最长是多少。A的任意子序列B可表示为$B={A_{k_1},A_{k_2},A_{k_3},\ldots,A_{k_p}}$，其中$k_1 < k_2 <\ldots<k_p$|
| 状态表示  |F[i]表示以A[i]为结尾的最长上升子序列的长度|
| 阶段划分 | 空间特征，子序列的结尾位置（数列A中的位置，从前到后） |
| 转移方程  |$F[i]=\underset{0 \le j \lt i,A[j] \lt A[i]}{\mathrm{max}}\{F[j] + 1\}$ 需要遍历j|
| 边界  | F[0]= 0|
| 目标  | $\underset{1 \le i \le N}{\mathrm{max}}{F[i]}$|
| 相关题目  | 俄罗斯信封套娃问题 |

|  LCS问题  | |
|  ----  | ----  |
| 问题描述   | 最长公共子序列。给定两个长度分别为N和M的字符串A和B，求即是A的子序列又是B的子序列的字符串长度最长是多少。|
| 状态表示  |F[i,j]表示前缀子串A[1-i]与B[1-j]的最长公共子序列的长度|
| 阶段划分 | 空间特征，已经处理的前缀长两个字符串中的位置，即一个二维坐标 |
| 转移方程  |$F[i,j]=\begin{cases}F[i,j-1] \\ F[i-1,j] \\ F[i-1,j-1] + 1 & \text{if } A[i] = B[j] \end{cases}$|
| 边界  | F[i,0]=F[0,j]=0|
| 目标  | $F[N,M]$|

|  数字三角形  | |
|  ----  | ----  |
| 问题描述   | 给定一个共有N行的三角矩阵A，其中第i行有i列。从左上角出发，每次可以向下方或者右下方走一步，最终到达底部。求把经过的所有位置上的数加起来，和最大是多少。|
| 状态表示  |F[i,j]表示从左上角走到第i行，第j列，和最大是多少|
| 阶段划分 | 空间特征，路径的结尾位置（矩阵中的行列位置），即一个二维坐标 |
| 转移方程  |$F[i,j]=A[i,j]+\begin{cases}F[i-1,j] \\ F[i-1,j-1] & \text{if } j \gt 1 \end{cases}$|
| 边界  | F[1,1]=A[1,1]|
| 目标  | $\underset{1 \le j \le N}{\mathrm{max}}{F[N,j]}$|

|  数字组合（01背包模型）  |背包问题系列 |
|  ----  | ----  |
| 问题描述   | $A_1,A_2,A_3,\dots,A_N$，权重分别为$W_1,W_2,W_3,\dots,W_N$|
| 状态表示  |F[i,j]表示使用前i个数字拼凑出体积为j的物品的最大权重|
| 阶段划分 | 主阶段：已经选择的数字，拼凑出的和是附加维度|
| 转移方程  |$F[i,j]=max(F[i-1,j], F[i-1,j-A_i] + W_i)$ 第一项是不选择第i个数字，第二项是选择第i个数字|
| 边界  | F[0,0]=1，其余为0|
| 目标  | F[N,M]|
| 空间优化  | 调整遍历顺序（V从大到小），确保可以用滚动数组，不会覆盖前值|
| 相关题目  | 划分数组为两个相等的子集|

|  数字组合（完全背包模型）  |背包问题系列 |
|  ----  | ----  |
| 问题描述   |$A_1,A_2,A_3,\dots,A_N$，权重分别为$W_1,W_2,W_3,\dots,W_N$|
| 状态表示  |F[i,j]表示使用前i个数字拼凑出体积为j的物品的最大权重|
| 阶段划分 | 主阶段：已经选择的数字，拼凑出的和是附加维度|
| 【优化前】转移方程  |$F[i,j]=max{F[i,j- k * A_i] + k * W_i, k * A_i < V}$ 第一项是不选择第i个数字，第二项是选择第i个数字|
| 【优化后】转移方程  |$F[i,j]=max(F[i-1,j], F[i,j-A_i])$ 第一项是不选择第i个数字，第二项是选择第i个数字|
| 边界  | F[0,0]=1，其余为0|
| 目标  | F[N,M]|
| 空间优化  | 调整遍历顺序（V从小到大），确保可以用滚动数组，不会覆盖前值|

|  数字组合（多重背包模型）  |背包问题系列 |
|  ----  | ----  |
| 问题描述   |$A_1,A_2,A_3,\dots,A_N$，权重分别为$W_1,W_2,W_3,\dots,W_N$，物品数量不超过$N_1,N_2,N_3,\dots,N_N$|
| 状态表示  |F[i,j]表示使用前i个数字拼凑出体积为j的物品的最大权重|
| 阶段划分 | 主阶段：已经选择的数字，拼凑出的和是附加维度|
| 【优化前】转移方程  |$F[i,j]=max{F[i,j- k * A_i] + k * W_i, k < N_i}$ 第一项是不选择第i个数字，第二项是选择第i个数字|
| 【优化后】转移方程  |把$N_i$拆分为二进制，然后转换为01背包问题|
| 边界  | F[0,0]=1，其余为0|
| 目标  | F[N,M]|
| 空间优化  | 调整遍历顺序（V从小到大），确保可以用滚动数组，不会覆盖前值|

|  最少硬币数  |换硬币系列 |
|  ----  | ----  |
| 问题描述   | 给定N种硬币，其中第i种面额为$C_i$，计算凑成总金额M所需的最少的硬币个数。每种硬币的数量是无限的。|
| 状态表示  |F[i]表示凑出金额i用的最小硬币数|
| 转移方程  |$F[i]=\underset{1 \le j \le N}{\mathrm{min}}{F[i - C_j] + 1}$|
| 边界  | F[0]=0，其余为正无穷|
| 目标  | F[M]|

|  求硬币拼凑的总方案数  |换硬币系列 |
|  ----  | ----  |
| 问题描述   | 给定N种硬币，其中第i种面额为$C_i$，计算凑成总金额M的所有方案数|
| 状态表示  |F[i,m]表示利用前i种硬币凑出金额m的方案数|
| 转移方程  |$F[i]=\sum\limits_{j=1}^{N} {F[i - C_j]}$|
| 边界  | F[0]=1，其余为0|
| 目标  | F[M]|

|  最大子数组  | |
|  ----  | ----  |
| 问题描述   |子数组和最大|
| 状态表示  |F[i]表示利用以d[i]结尾的子数组的最大和|
| 转移方程  |$F[i]= max(F[i-1] + A_i, A_i)$，其实等价于判断F[i-1]是否小于0|
| 边界  | F[0]=1，其余为0|
| 目标  | F[M]|
| 相关题目  | 乘积最大连续子数组\最大子矩阵：i~j列上的数字进行加和，然后二维转一维|
| 相关题目  | 环形最大子数组：Copy一遍，长度*2，然后限制长度不超过n|
| 相关题目  | 环形最大子数组：max(【跨末端】Sum - 最小子数组, 【原】最大子数组)|

|  股票买卖  | |
|  ----  | ----  |
| 问题描述   | 交易K次 |
| 状态表示  |F[Day, MaxTradeCnt, FullOrShort]表示利用前Day天，交易次数剩余MaxTradeCnt, 空仓满仓时能够获得的最大利润|
| 转移方程  |$F[i,k,0]=max(F[i-1, k, 0], F[i-1,k,1] + prices[i])$|
| 转移方程  |$F[i,k,1]=max(F[i-1, k, 1], F[i-1,k-1,0] - prices[i])$|
| 边界  | F[0]=1，其余为0|
| 目标  | F[M]|
| 相关题目  | 交易一次，交易无限次，交易K次|

|  字符串编辑距离问题  | |
|  ----  | ----  |
| 问题描述   |strA与strB变为一样所需要的最少操作次数|
| 状态表示  | L(i,j)为使两个字符串和Ai和Bj相等的最小操作次数；Ai表示前i个字符|
| 转移方程  |$L(i,j) = min( L(i-1,j-1), L(i-1,j), L(i,j-1) ) + 1$|

|  最长回文串  | |
|  ----  | ----  |
| 问题描述   ||
| 状态表示  |F[i][j] 表示 S[i] 至 S[j] 所表示的子串是否是回文子串|
| 转移方程  |$F[i,j]=\begin{cases}F[i+1,j-1] \text{if } S_i = S_j \\ 0 & \text{if } S_i \ne S_j \end{cases}$|

|  正则匹配  | |
|  ----  | ----  |
| 问题描述   | |
| 状态表示  ||
| 转移方程  |见：https://leetcode.cn/problems/regular-expression-matching/solution/zheng-ze-biao-da-shi-pi-pei-by-leetcode-solution/|

|  扔鸡蛋问题  | |
|  ----  | ----  |
| 问题描述   |dp[i,j]表示i层，j个鸡蛋，最坏情况下的最少扔鸡蛋次数|
| 转移方程  |$dp(N,K)=\underset{1 \le i \le N}{\mathrm{min}}(1+max(dp(N-i,K), dp(i-1,K-1)))$|
| 具体实现  |状态扭转特别复杂，用for循环有点困难，所以我们采用DFS + 记忆化搜索，时间复杂度：$O(N*N*K)$；上面方程中的i啥意思？他表示对于要探测的N层，有N种选择；我需要挨个去做**选择**，而不是在枚举**状态**；状态的枚举是通过DFS递归来实现的|
| 二分搜索优化  |dp(N-i,K)与dp(i-1,k-1) 总是一个单调递增，一个单调递减；所以什么时候最小呢？所以两者的直线交点即为最小值；这种思路类似于峰谷问题，可以用二分解决！把时间复杂度将为$O(N * K * LgN)$|

|  扔鸡蛋问题-进阶  | |
|  ----  | ----  |
| 问题描述   |F[i,j]表示最多允许i个鸡蛋，当前已经扔了j个，能确定的最高楼层数|
| 转移方程  |$dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1$|

## 动态规划相关的经典题目

|  题目分类 | 题目名称 |考察点   |其他说明|
|  ----  | ---- |----  |----  |
| 二维DP | [棋盘上获取最大价值的礼物](getMaxValue.html)  ||
| 字符串DP | [获取不同的翻译方法次数](getTranslationCount.html)  ||
| 二维DP | [求解一个矩阵中找一条最长的递增路径](long_path_in_2d_array.html)  ||
| 二维DP | [骰子点数](num_of_slices.html)  ||
| | [股票买卖系列](stock_common.html)  ||
| | [子数组最大和](sub_array_sum_max.html)  |子数组最大和问题|

https://zhuanlan.zhihu.com/p/410411231

等差递减区间的个数【转斐波那契】