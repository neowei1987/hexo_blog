---
title: 计算机解决问题的通用套路
date: 2021-01-07 13:01:03
mathjax: true
categories:
- 算法基础
tags: 
- 
---

## 什么是熵？(Entropy)

熵，代表了一个系统的混乱程度。一个系统越混乱，其熵越大。一个封闭系统的熵随着时间推移，会一直变大，且不可逆。

![熵增定律](http://cdn.b5mang.com/202118134321.png)

## 什么是信息熵？(Information Entropy)

一条信息的信息量大小和它的不确定性有直接的关系。不确定性越大，其信息量越大。我们用信息熵被用来计算信息量，其计算公式如下：
H(x) = -∑p(xi)log(p(xi)) (i=1,2,..n)    （其中p(x)是x事件出现的概率），信息熵的单位是bit。

获得了新的信息后，不确定性减少，信息熵降低。

## 问题的解空间与信息熵的关系

这里提一个很重要的概念：问题的解空间。什么是问题的解空间呢？所有可能成为问题最优解的解所构成的空间。问题的解空间越大，不确定性就越大，问题就“越混乱”，熵也就越高。

计算机求解问题的过程是怎样的呢？计算机算法在执行的过程中，获取更多信息，将要解决的问题的信息熵减小，直到减到0，该问题就被解决了。

每一个问题都有一个固有的初始信息熵，这个初始信息熵的大小也就决定了这个问题的复杂程度。例如，N皇后这个问题就比“从N个数中找到最大值”问题更难，因为前者的解空间更大，有更多的可能性。

![问题的信息熵与其解空间大小的关系](http://cdn.b5mang.com/2021181698.png)

不同的算法为什么执行时间差别那么大？

![算法执行时间与信息熵的关系](http://cdn.b5mang.com/202118164152.png)

同一个问题，有不同的解法，也就会产生不同的解空间。

一开始的时候，要解决的问题信息熵很大，不确定性就越大。从信息熵的角度来看，就是把这个问题的熵将为0的过程。
什么是问题的求解呢？
计算机算法是如何获取新的信息的呢？ 信息获取的越快，
举个例子，从N个数中找到某一个数这个问题。一开始这个问题有N种可能性，
搜索空间就是你算法的自变量构成的空间，而求解问题的解空间是你问题的解构成的空间。所以当你算法的自变量范围和求解问题的解范围相同时，这两个空间就是相同的。但是在很多时候，它们并不相同。这是因为求解的问题往往存在约束。大多数情况下，我们在处理约束时，都是采用惩罚函数的方式。这相当于我们把求解问题对解的约束放在了目标函数上。由此，变相地放大了自变量的空间，也就是算法的搜索空间。

让我们结合几个例子来

## 常见问题的解空间有多大

子集问题
$2^k$

组合问题


排列问题
n!


参考文章：
https://stonema.github.io/2018/03/27/大话交叉熵/


一条信息的信息量大小和它的不确定性有直接的关系。比如说，我们要搞清楚一件非常非常不确定的事，或是我们一无所知的事情，就需要了解大量的信息。相反，如果我们对某件事已经有了较多的了解，我们不需要太多的信息就能把它搞清楚。所以，从这个角度，我们可以认为，信息量的度量就等于不确定性的多少。（摘自数学之美）

香浓指出的信息熵的计算公式如下（本文的对数一律以2为准）

H(x) = -∑p(xi)log(p(xi)) (i=1,2,..n)    （其中p(x)是x事件出现的概率）单位为bit
算法时间复杂度，与信息熵

数学之美里是用赛后怎么知道32个球队里谁是冠军来讲解了这个信息熵的概念。

当概率相等时，每次询问用折半查找的原理（如“冠军队伍在1-16吗？”）可以减少一半的队伍，这样就需要5次就能知道结果了。这里就是log32 = 5

而使用信息熵计算信息量，的确也是5。但是为什么信息熵这个公式会代表信息量呢


按我的理解，在等概率事件里，1/p(x) 代表那一次所有可能出现的量、在球队问题里，就是32种可能性。

而等概率事件里，因∑p（xi） = 1，所以信息熵可以看成

信息熵H(x)= -∑p(xi)log(p(xi)) (i=1,2,..n) = -log(p(i)) = -（- log（1/p(x)））= log（1/p(x)）


也就是说等概率事件里的信息量可以看成

H（x）= log（所有可能性）


为了加深对信息量的定义的理解，再回到上述32个球队的问题，我们已经知道他的信息量是5Bit

问过一次之后，我们可以知道冠军在哪16个队伍中，也就是说我们获得了1bit的信息后不确定性减少，等于信息熵变成了log16 = 4bit =5bit -1bit

而最大熵模型呢？它的原理就是保留全部的不确定性，将风险降到最少。

最大熵原理指出，当我们需要对一个随机事件的概率分布进行预测时，我们的预测应当满足全部已知的条件，而对未知的情况不要做任何主观假设。（不做主观假设这点很重要。）在这种情况下，概率分布最均匀，预测的风险最小。因为这时概率分布的信息熵最大，所以人们称这种模型叫“最大熵模型”。我们常说，“不要把所有的鸡蛋放在一个篮子里”，其实就是最大熵原理的一个朴素的说法，因为当我们遇到不确定性时，就要保留各种可能性。

也就是说发现不确定信息的时候，不要对不确定的产物任何主观假设使他们的概率分布均匀，则能获得最客观的结果。而这时风险会最小，我们就可以用这个结果来进行最客观的决策。数学上来说貌似就是最优下界吧。这种策略的本质可以概括成“让未知世界无机可乘”。它是没有“弱点的”，答案的任何一个分支都是等概率的。反之，一旦某个分支蕴含的可能性更多，当情况落到那个分支上的时候你就郁闷了。二分搜索为什么好，就是因为它每次都将可能性排除一半并且无论如何都能排除一半（它是最糟情况下表现最好的）。（摘自mindhacks快排为什么那么快）

我再用算法的时间复杂度说明一下最大熵原理吧，用几个主流的算法对n个数据进行排序时间复杂度基本上都是从O（nlogn）到O（n2）。而一般情况下为什么O（nlogn）最优呢，因为n个数据的先后顺序是随机的，我们可以看做不确定性相等，则可以用最大熵原理获得最优(最稳定)结果。则信息熵则为

H(x)= log（所有可能性）= log（n！） 而n—>00 则log（n！）近似于lognn= nlogn

假设我们每次能获得1bit数据，就至少需要获得（nlogn）bit数据才能取消信息的不确定性，也就是要比较nlogn次。但因为各种排序算法策略不同，我们不可能每次都能获得1bit数据，所以按照信息熵的定义这是理论上最优的结果。而最佳的排序算法就是要每次获得1bit数据，越接近于1则越有效。

而TopLanguage那个帖子里也说了，虽然快排和堆排序两个是都是时间复杂度O（nlogn）的算法,但是快速排序一般都会比堆排序快，就是因为堆排序每次获取的平均信息量比快排来的低。

而上面，我们根本没提到具体算法，就算到了最优的时间复杂度。在实际生活中很多时候我们虽然不会想到具体的策略，但我们至少可以知道极限在哪里，可以知道还有没有提高余地。任何排序和猜数字的算法可以理解为通过获得信息量去消减原来的熵。（这句摘自eric的话）

什么叫状态空间树？
就是问题的解空间树，分为子集树和排列树

当所给的问题是从n个元素的集合S中找到S满足某种性质的子集时，相应的解空间树称为子集树。

当所给问题是确定n个元素满足某种性质的排列时，相应的解空间树称为排列树。

子集树和排列树的不同是每一步的选择策略不同。子集树每一步对应的是对应的元素的选择或不选择，排列树每一步对应的是剩下的元素选择其中一个。一个的可搜索的解为2**n，一个为n！，因此，一个高效的回溯法算法必须依赖于剪枝函数来避免无效搜索。

面对许多实际问题时，需要求解满足特定条件的全部解或最优解，如著名的N皇后问题和旅行售货员问题。
此类问题，一般没有特定的计算规则用于解题，通常我们采用试探性的方法，在包含问题所有可能解的解空间树中，将所有可能的结果搜索一遍，从而获得我们期望的那一个解，或者是那一些解，一般就是满足一定条件的最优解，或是全部解。那么这里用到的解空间树是什么呢？

解空间树：
依据待解问题的特性，用树结构表示问题的解结构，用叶子表示所有问题所有可能解的一棵树。

解空间树的建立：
就是将问题求解的一系列判断决策过程及各种可能的结果用树型结构呈现。
事实上，我们解题的过程是一个不断判断决策的过程，我们把每一步判断决策的过程对应于解空间树的一个分支结点，而各种可能的不同结果，则对应得到结点的每一个孩子及各棵子树，而一系列判断决策的解题过程，就对应着解空间树的生长过程；而问题最终所有可能的解，都会呈现在这棵解空间树的叶子上。

让我们先思考下我们之前做过的算法题都有哪些种类？



解空间树T

回溯法以深度优先的方式搜索解空间树T，而分支限界法则以广度优先或以最小耗费优先的方式搜索解空间树T。它们在问题的解空间树T上搜索的方法不同，适合解决的问题也就不同。一般情况下，回溯法的求解目标是找出T中满足约束条件的所有解的方案，而分支限界法的求解目标则是找出满足约束条件的一个解，或是在满足约束条件的解中找出使某一目标函数值达到极大或极小的解，即在某种意义下的最优解。相对而言，分支限界算法的解空间比回溯法大得多，因此当内存容量有限时，回溯法成功的可能性更大。

发现当考虑了所有的操作时，还要对操作所得状态进行判断，是否已出现过，来避免重复搜索。这道题我纠结了好久，就是因为我想通过限制操作来避免出现重复状态，而出现重复状态的情况有很多，很难考虑全面。其实判断状态是否重复我之前也都做过，就是在搜索迷宫的过程中，操作就是移动的方向，而状态就是位置，为了避免重复搜索就在地图上做标记，当时这样做的时候觉得顺理成章，不过在这题里，却并没有能直接这样做。
总结下，在搜索整个解空间时，首先是考虑所有的 操作，然后通过保存已出现 状态，来防止重复搜索。如果很容易通过对操作进行限制来防止状态的重复出现，或是保存状态所需的内存空间过大的话，那就不宜保存状态。


 a computational problem is a problem that a computer might be able to solve or a question that a computer may be able to answer.
 A computational problem can be viewed as an infinite collection of instances together with a, possibly empty, set of solutions for every instance. For example, in the factoring problem, the instances are the integers n, and solutions are prime numbers p that describe nontrivial prime factors of n.

A **decision problem** is a computational problem where the answer for every instance is either yes or no.

In a **search problem**, the answers can be arbitrary strings. For example, factoring is a search problem where the instances are (string representations of) positive integers and the solutions are (string representations of) collections of primes.

决策问题，给定一个正整数n，确定n是否是素数。

搜索问题，找到一个正整数的所有非朴素因子。

A counting problem asks for the number of solutions to a given search problem. For example, a counting problem associated with factoring is

"Given a positive integer n, count the number of nontrivial prime factors of n."

An **optimization problem** asks for finding a "best possible" solution among the set of all possible solutions to a search problem.

求这n个实数在数轴上相邻2个数之间的最大差值，

In a **function problem** a single output (of a total function) is expected for every input, but the output is more complex than that of a decision problem, that is, it isn't just "yes" or "no". One of the most famous examples is the traveling salesman problem:

"Given a list of cities and the distances between each pair of cities, find the shortest possible route that visits each city exactly once and returns to the origin city."
It is an NP-hard problem in combinatorial optimization, important in operations research and theoretical computer science.

![function problem](http://cdn.b5mang.com/202117132959.png)

我们要解决一个

当不确定性降到了0，问题就解决了。

信息：

熵：

高熵特征，低熵特征

熵增定律

多做一步的目的是为了减少更多的不确定性。