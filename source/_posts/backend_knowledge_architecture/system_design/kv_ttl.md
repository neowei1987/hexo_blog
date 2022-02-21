设计一个带有有效时间TTL的KV存储系统，包含set（key，value，ttl）、get（key）方法、怎么优化

首先是KV存储，可以使用LogStructuredTree

把TTL当作value

党进行compaction时，过期的数据会被忽略。