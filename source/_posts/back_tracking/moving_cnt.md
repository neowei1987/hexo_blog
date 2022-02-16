
地上有一个 m 行和 n 列的方格，横纵坐标范围分别是 0∼m−1 和 0∼n−1。

一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格。

但是不能进入行坐标和列坐标的数位之和大于 k 的格子。

请问该机器人能够达到多少个格子？

样例1
输入：k=7, m=4, n=5

输出：20
样例2
输入：k=18, m=40, n=40

输出：1484

解释：当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。
但是，它不能进入方格（35,38），因为3+5+3+8 = 19。

```cpp
class Solution {
public:
    int t;
    vector<bool> visit;
    int cnt;
    
    bool check(int i, int j) {
        return (i / 10 + i % 10 + j / 10 + j % 10) <= t;
    }
    
    void dfs(int i, int j, int rows, int cols){
        if (!check(i, j)) return;
        visit[i * cols + j] = true;
        cnt++;
        
        int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
        
        for (int k = 0; k < 4; ++k) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !visit[ni * cols + nj]) {
                dfs(ni, nj, rows, cols);
            }
        }
    }
    
    int movingCount(int threshold, int rows, int cols)
    {
        if (!rows && !cols) return 0;
        t = threshold;
        visit = vector<bool>((rows + 1) * (cols + 1), false);
        dfs(0, 0, rows, cols);
        return cnt;
    }
};
```