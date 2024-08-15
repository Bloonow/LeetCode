#include <string>
#include <vector>
using namespace std;

// 5. 最长回文子串
// 动态规划
class Solution {
public:
    string longestPalindrome(string s) {
        int length = s.length();
        if (length == 1) return s;
        if (length == 2 && s[0] == s[1]) return s;
        // 元素 dp[i][j] 表示子字符串 s[i...j] 是否是回文串
        vector<vector<int>> dp(length, vector<int>(length, false));
        for (int i = 0; i < length; i++) dp[i][i] = true;
        int start = 0, len = 1;
        for (int i = 0; i <= length - 2; i++) {
            dp[i][i + 1] = s[i] == s[i + 1];
            if (dp[i][i + 1]) {
                start = i;
                len = 2;
            }
        }
        for (int cur_len = 3; cur_len <= length; cur_len++) {
            for (int i = 0; i < length - cur_len + 1; i++) {
                dp[i][i + cur_len - 1] = dp[i + 1][i + cur_len - 2] && (s[i] == s[i + cur_len - 1]);
                if (dp[i][i + cur_len - 1]) {
                    start = i;
                    len = cur_len;
                }
            }
        }
        return s.substr(start, len);
    }
};