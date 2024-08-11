#include <string>
#include <vector>
using namespace std;

// 1143. 最长公共子序列
// 动态规划，最优子结构性质，子问题重复性质
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int M = text1.length(), N = text2.length();
        // 元素 dp[i][j] 表示 text1[0...i] 和 text2[0...j] 的最长公共子串
        vector<vector<int>> dp(M, vector<int>(N, 0));
        dp[0][0] = text1[0] == text2[0] ? 1 : 0;
        for (int k = 1; k < M; k++) {
            dp[k][0] = text2[0] == text1[k] ? 1 : dp[k - 1][0];
        }
        for (int k = 1; k < N; k++) {
            dp[0][k] = text1[0] == text2[k] ? 1 : dp[0][k - 1];
        }
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[M - 1][N - 1];
    }
};