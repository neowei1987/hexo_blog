假设一个单调递增的数组里的每个元素都是整数并且是唯一的。

请编程实现一个函数找出数组中任意一个数值等于其下标的元素。

例如，在数组[-3, -1, 1, 3, 5]中，数字3和它的下标相等。

样例
输入：[-3, -1, 1, 3, 5]

输出：3
注意:如果不存在，则返回-1。

```cpp
class Solution {
public:
    int getNumberSameAsIndex(vector<int>& nums) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= mid) {
                r = mid;
            }
            else { //[mid + 1, r] 都不可能满足满足；因为递增
                l = mid + 1;
            }
        }

        if (nums[r] != r) {
            return -1;
        }
        else {
            return r;
        }
    }
};
```