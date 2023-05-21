---
title: sk learn介绍
tags:
mathjax: true
---

sk learn的六大功能：

分类

回归

聚类


预处理

模型选择

降维

8:2 
cross validation

Training 切成N份（例如10）

选前9份，进行交叉验证，对结果进行平均（准确率一般平均）。
Validation 验证数据

Testing 比较宝贵

confusion matrix 混淆矩阵，relative with 召回率，准确率

TruePostive     FalsePostive
FalseNegative   TrueNegative

True 做到了
Postive 正类

评价指标有几个：

recall 召回率

precision 准确率

F1 score (调和平均数) = 2 / （1 + precision） + 1 (1 + recall) 给予低值更高的权重

various **thresholds**(阈值就是要求，越高越严格！) 跟 score比较 

predict = score > thresholds : True : False

随着thresholds从低到高，精确率上升，召回率降低；

准确率-召回率曲线

ROC curves (ROC曲线)

AUC 测量曲线下面积（综合评估），最好是1，最差是0.5
