给定一个长度为 n+1 的数组nums，数组中所有的数均在 1∼n 的范围内，其中 n≥1。

请找出数组中任意一个重复的数，但不能修改输入的数组。

样例
给定 nums = [2, 3, 5, 4, 3, 2, 6, 7]。

返回 2 或 3。

思考题：如果只能使用 O(1) 的额外空间，该怎么做呢？

思考： 把肯定不符合条件的一半给忽略掉；

```cpp
class Solution {
public:
    int duplicateInArray(vector<int>& nums) {
        int l = 1, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) >> 1;  //[l, mid], [mid + 1, r]
            int s = 0;
            /注意这里是遍历了所有的元素
            for (int i = 0; i < nums.size(); ++i) s += (nums[i] >= l && nums[i] <= mid);
            if (s > (mid - l + 1)) r = mid;
            else l = mid + 1; //数量不够，说明这个区间内的某个数肯定被替换掉了，所以肯定在另外一边。
        }
        
        return r;
    }
};
```
