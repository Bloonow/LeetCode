#include <vector>
using namespace std;

// 73. 矩阵置零
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int M = matrix.size();
        int N = matrix[0].size();
        bool col0_zero = false, row0_zero = false;
        for (int i = 0; i < M; i++) {
            if (matrix[i][0] == 0) {
                col0_zero = true;
            }
        }
        for (int j = 0; j < N; j++) {
            if (matrix[0][j] == 0) {
                row0_zero = true;
            }
        }
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (col0_zero) {
            for (int i = 0; i < M; i++) {
                matrix[i][0] = 0;
            }
        }
        if (row0_zero) {
            for (int j = 0; j < N; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
