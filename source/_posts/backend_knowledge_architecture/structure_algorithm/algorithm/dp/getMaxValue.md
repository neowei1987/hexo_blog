在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于0）。

你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格直到到达棋盘的右下角。

给定一个棋盘及其上面的礼物，请计算你最多能拿到多少价值的礼物？

注意：

m,n>0
样例：

输入：
[
[2,3,1],
[1,7,1],
[4,6,1]
]

输出：19

解释：沿着路径 2→3→7→6→1 可以得到拿到最大价值礼物。

```cpp
class Solution {
public:
    typedef pair<int, int> PII;
    int res;
    int m;
    int n;
    vector<vector<int>> grid;
    vector<vector<int>> dp;
    
    /*
    void dfs(int x, int y, int sum) {
        if (x == m - 1 && y == n -1) {
            res = max(res, sum);
            return;
        }
        
        int dx[] = {0, 1};
        int dy[] = {1, 0};
        for (int k = 0; k < 2; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] >= 0) {
                int b = grid[nxa][ny];
                grid[nx][ny] = -1;
                dfs(nx, ny, sum + b);
                grid[nx][ny] = b;
            }
        }
    }
    
    int getMaxValue(vector<vector<int>>& _grid) {
        grid = _grid;
        m = grid.size();
        n = grid[0].size();
        dfs(0, 0, grid[0][0]);
        return res;
    }
    */
    

     int dfs(int i, int j) {
        if (dp[i][i] >= 0) {
            return dp[i][j];
        }
        
        if (i == 0 && j == 0) {
            return dp[i][j] = grid[i][j];
        }
        
        dp[i][j] = grid[i][j] + max(
                                j - 1 >= 0 ? dfs(i, j - 1) : INT_MIN, 
                                i - 1 >= 0 ? dfs(i - 1, j) : INT_MIN);
        return dp[i][j];
    }
    
    int getMaxValue(vector<vector<int>>& _grid) {
        grid = _grid;
        m = grid.size();
        n = grid[0].size();
        dp = vector<vector<int>>(m, vector<int>(n, -1));
        dfs(m - 1, n - 1);
        return dp[m - 1][n - 1];
    }
};
```
