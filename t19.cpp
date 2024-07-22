#include <vector>
using namespace std;

// 54. 螺旋矩阵
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int M = matrix.size();
        int N = matrix[0].size();
        int total_circle = (min(M, N) + 1) / 2;
        vector<int> rets(M * N);
        int idx = 0, has = 0;
        for (int circle = 0; circle < total_circle; circle++) {
            has = (N - 1 - circle) - (circle) + 1;
            if (has <= 0) continue;
            for (int i = 0; i < has; i++) {
                rets[idx++] = matrix[circle][circle + i];
            }
            has = (M - 1 - circle) - (circle + 1) + 1;
            if (has <= 0) continue;
            for (int i = 0; i < has; i++) {
                rets[idx++] = matrix[circle + 1 + i][N - 1 - circle];
            }
            has = (N - 2 - circle) - (circle) + 1;
            if (has <= 0) continue;
            for (int i = 0; i < has; i++) {
                rets[idx++] = matrix[M - 1 - circle][N - 2 - circle - i];
            }
            has = (M - 2 - circle) - (circle + 1) + 1;
            if (has <= 0) continue;
            for (int i = 0; i < has; i++) {
                rets[idx++] = matrix[M - 2 - circle - i][circle];
            }
        }
        return rets;
    }
};
