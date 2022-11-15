矩阵90度旋转

```cpp
class Solution {
public:
    vector<vector<int> > rotateMatrix(vector<vector<int> > mat, int n) {
        //水平翻转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(mat[i][j], mat[n - 1 - i][j]);
            }
        }

        //对角线翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        return mat;
    }
};
```