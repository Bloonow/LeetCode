#include <vector>
using namespace std;

// 74. 搜索二维矩阵
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int M = matrix.size(), N = matrix[0].size();
        int ri = 0, rj = M - 1, ci = 0, cj = N - 1;
        while (ri <= rj) {
            int mid = (ri + rj) / 2;
            if (matrix[mid][0] == target) {
                return true;
            } else if (target < matrix[mid][0]) {
                rj = mid - 1;
            } else /* matrix[mid][0] < target */ {
                ri = mid + 1;
            }
        }
        int row = min(ri, rj);
        if (row < 0) row = 0;
        if (row >= M) row = M - 1;
        while (ci <= cj) {
            int mid = (ci + cj) / 2;
            if (matrix[row][mid] == target) {
                return true;
            } else if (target < matrix[row][mid]) {
                cj = mid - 1;
            } else /* matrix[row][mid] < target */ {
                ci = mid + 1;
            }
        }
        return false;
    }
};