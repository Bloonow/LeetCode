#include <vector>
using namespace std;

// 64. 最小路径和
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        vector<vector<int>> dp(M, vector<int>(N, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < M; i++) dp[i][0] = grid[i][0] + dp[i - 1][0];
        for (int j = 1; j < N; j++) dp[0][j] = grid[0][j] + dp[0][j - 1];
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[M - 1][N - 1];
    }
};