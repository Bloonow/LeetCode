#include <vector>
using namespace std;

// 48. 旋转图像
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int N = matrix.size();
        int total_circle = (N + 1) / 2;
        for (int circle = 0; circle < total_circle; circle++) {
            int has = (N - 1 - circle) - circle;
            if (has < 1) break;
            for (int i = 0; i < has; i++) {
                int tmp = matrix[N - 1 - circle - i][circle];
                matrix[N - 1 - circle - i][circle] = matrix[N - 1 - circle][N - 1 - circle - i];
                matrix[N - 1 - circle][N - 1 - circle - i] = matrix[circle + i][N - 1 - circle];
                matrix[circle + i][N - 1 - circle] = matrix[circle][circle + i];
                matrix[circle][circle + i] = tmp;
            }
        }
    }
};
