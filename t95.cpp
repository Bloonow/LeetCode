#include <string>
#include <vector>
#include <stack>
using namespace std;

namespace S1 {
// 72. 编辑距离
// 先找最长公共子序列，并将 word1 和 word2 按公共序列对齐，然后，在将 word1 转变为 word2 的过程中，
// 由 word1 ---> word2 过程中，不同的字母要修改，多余的字母要删除，缺少的字母要插入
// 过程需要记录公共序列的字母，以及该字母在两个字符串中的位置
// 【答案错误】只能找到最后一个最长公共子序列，而存在多个最长公共子序列时，根据不同的子序列进行修改，所需的编辑距离并不相同，
// 例如 "mart" 和 "karma"，根据子序列 ma 需要 5 次修改，而根据 ar 则需要 3 次修改
class Solution {
public:
    struct P {
        int x, y;
        P(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    };
    int minDistance(string word1, string word2) {
        int M = word1.length(), N = word2.length();
        if (M == 0) return N;
        if (N == 0) return M;
        // 元素 dp[i][j] 表示 word1[0...i] 和 word2[0...j] 的最长公共子串
        vector<vector<int>> dp(M, vector<int>(N, 0));
        dp[0][0] = word1[0] == word2[0] ? 1 : 0;
        int max_length = 0;
        // 相等字母在两个字符串中的索引，-1 表示不存在
        vector<vector<P>> path(M, vector<P>(N, { -1, -1 }));
        path[0][0] = word1[0] == word2[0] ? P(0, 0) : P(-1, -1);
        for (int k = 1; k < M; k++) {
            if (word2[0] == word1[k]) {
                dp[k][0] = 1;
                path[k][0] = P(k, 0);
            } else {
                dp[k][0] = dp[k - 1][0];
                path[k][0] = path[k - 1][0];
            }
        }
        for (int k = 1; k < N; k++) {
            if (word1[0] == word2[k]) {
                dp[0][k] = 1;
                path[0][k] = P(0, k);
            } else {
                dp[0][k] = dp[0][k - 1];
                path[0][k] = path[0][k - 1];
            }
        }
        int last_i = M - 1, last_j = N - 1;
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    path[i][j] = P(i, j);
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    if (word1[i - 1] == word2[j]) {
                        path[i][j] = path[i - 1][j];
                    } else if (word1[i] == word2[j - 1]) {
                        path[i][j] = path[i][j - 1];
                    } else {
                        path[i][j] = path[i - 1][j - 1];
                    }
                }
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    last_i = i;
                    last_j = j;
                }
            }
        }
        // 接下来构造公共子序列
        stack<P> common;
        int i = last_i, j = last_j;
        while (i >= 0 && j >= 0 && path[i][j].x >= 0 && path[i][j].y >= 0) {
            common.push(path[i][j]);
            i = common.top().x - 1;    // 在 word1 中的索引
            j = common.top().y - 1;   // 在 word2 中的索引
        }
        // 接下来根据公共子序列，寻找应该修改之处
        int i1 = -1, j1 = -1, i2 = -1, j2 = -1;
        int count = 0;
        while (!common.empty()) {
            i2 = common.top().x;
            j2 = common.top().y;
            common.pop();
            count += max(i2 - i1 - 1, j2 - j1 - 1);
            i1 = i2;
            j1 = j2;
        }
        // 结尾之处
        count += max(M - 1 - i2, N - 1 - j2);
        return count;
    }
};
}

namespace S1 {
// 72. 编辑距离
// 动态规划
class Solution {
public:
    int minDistance(string word1, string word2) {

    }
};
}