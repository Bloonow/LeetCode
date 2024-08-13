#include <vector>
using namespace std;

namespace S1 {
// 240. 搜索二维矩阵 II
/* 先确定可能范围，再遍历
⚫⚫⚫⚫⚫⚫
⚫⚫⚫🟢🟢⚫
⚫⚫⚫🟢🟢⚫
⚫⚫⚫🟢🟢⚫
⚫⚫⚫🟢🟢⚫
⚫⚫⚫⚫⚫⚫
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int M = matrix.size(), N = matrix[0].size();
        int row_start = 0, row_end = M;
        int col_start = 0, col_end = N;
        for (int i = 0; i < N; i++) {
            if (matrix[0][i] == target) return true;
            if (matrix[0][i] > target) {
                col_end = i; break;
            }
        }
        for (int i = 0; i < M; i++) {
            if (matrix[i][0] == target) return true;
            if (matrix[i][0] > target) {
                row_end = i; break;
            }
        }
        for (int i = col_end - 1; i >= 0; i--) {
            if (matrix[row_end - 1][i] == target) return true;
            if (matrix[row_end - 1][i] < target) {
                col_start = i + 1; break;
            }
        }
        for (int i = row_end - 1; i >= 0; i--) {
            if (matrix[i][col_end - 1] == target) return true;
            if (matrix[i][col_end - 1] < target) {
                row_start = i + 1; break;
            }
        }
        for (int i = row_start; i < row_end; i++) {
            for (int j = col_start; j < col_end; j++) {
                if (matrix[i][j] == target) return true;
            }
        }
        return false;
    }
};
}

namespace S2 {
// 240. 搜索二维矩阵 II
/* 从右上角开始，以 ━┓ 形状查找
🟢🟢🟢🟢🟢🟠
⚫⚫⚫⚫⚫🟢
⚫⚫⚫⚫⚫🟢
⚫⚫⚫⚫⚫🟢
⚫⚫⚫⚫⚫🟢
⚫⚫⚫⚫⚫🟢
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int M = matrix.size(), N = matrix[0].size();
        int X = 0, Y = N - 1;
        while (X <= M - 1 && Y >= 0) {
            if (matrix[X][Y] == target) {
                return true;
            } else if (matrix[X][Y] < target) {
                X++;
            } else {
                Y--;
            }
        }
        return false;
    }
};
}