
设计目标：
高性能，更快的找到下一个超时的Task
高分辨率，例如毫秒定时器

实现方式：
时间轮
基于时间堆
多级时间轮
基于排序链表 O(N)
红黑树

时间堆
数据结构：堆
思路：将所有定时器中超时时间最小定时器的timeout作为心搏的间隔。这样，当tick（）被调用时，超时时间最小的定时器必然到期