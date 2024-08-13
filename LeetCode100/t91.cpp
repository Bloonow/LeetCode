#include <vector>
using namespace std;

namespace S1 {
// 62. 不同路径
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int endX = m - 1, endY = n - 1;
        dp[endX][endY] = 1;  // 起始位置
        while (endX >= 0 && endY >= 0) {
            if (endX + 1 <= m - 1) dp[endX][endY] += dp[endX + 1][endY];
            if (endY + 1 <= n - 1) dp[endX][endY] += dp[endX][endY + 1];
            for (int i = endX - 1; i >= 0; i--) {
                dp[i][endY] += dp[i + 1][endY];
                if (endY + 1 <= n - 1) dp[i][endY] += dp[i][endY + 1];
            }
            for (int j = endY - 1; j >= 0; j--) {
                dp[endX][j] += dp[endX][j + 1];
                if (endX + 1 <= m - 1) dp[endX][j] += dp[endX + 1][j];
            }
            endX--;
            endY--;
        }
        return dp[0][0];
    }
};
}

namespace S2 {
// 62. 不同路径
// 从左上角到右下角的过程中，我们需要移动 m + n - 2 次，其中有 m - 1 次向下移动，n - 1 次向右移动
// 因此路径的总数，就等于从 m + n - 2 次移动中选择 m - 1 次向下移动的方案数，即组合数 C{m-1}{m+n-2}
class Solution {
public:
    int uniquePaths(int m, int n) {
        long long ans = 1;
        for (int x = n, y = 1; y < m; ++x, ++y) {
            ans = ans * x / y;
        }
        return ans;
    }
};
}