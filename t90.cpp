#include <string>
#include <vector>
#include <stack>
using namespace std;

namespace S1 {
// 32. 最长有效括号
// 动态规划，有效子串的长度肯定是偶数
class Solution {
public:
    int longestValidParentheses(string s) {
        int length = s.length();
        vector<int> dp(length, 0);  // 元素 dp[i] 表示在考虑 i 位置后，所能构成的最长有效子串
        int has_left = 0;
        int max_length = 0;
        for (int i = 0; i < length; i++) {
            char ch = s[i];
            if (ch == '(') {
                has_left++;
                continue;
            } else /* ch == ')' */ {
                if (has_left <= 0) {
                    continue;  // 多余的右括号，抛弃
                } else /* has_left > 0 */ {
                    has_left--;
                    int prev = i - 1;
                    bool has_find_my_left = false;
                    while (prev >= 0) {
                        if (s[prev] == ')' && dp[prev] != 0) {
                            dp[i] += dp[prev];
                            prev -= dp[prev];
                        } else if (s[prev] == '(') {
                            if (has_find_my_left == false) {
                                has_find_my_left = true;
                                prev--;
                            } else {
                                break;  // 多余的左括号
                            }
                        } else /* s[prev] == ')' && dp[prev] == 0 */ {
                            break;      // 多余的右括号
                        }
                    }
                    dp[i] += 2;
                }
                max_length = max(max_length, dp[i]);
            }
        }
        return max_length;
    }
};
}

namespace S2 {
// 32. 最长有效括号
// 使用栈
// 对于一个有效的括号序列而言，其最左侧一定是以 ( 开头，最右侧一定是以 ) 结尾；
// 对于一个新序列而言，若其第一个是 ) 括号，则该右括号一定无法构成有效序列，跳过该多余的无效右括号
// 于是，在一个有效子序列的左边，一定会是一个无效的右括号，或者是空；使用有效子序列的最右端位置，减去前一个无效位置，即得到长度
// 为统一左侧的无效情况，在最开始的左侧，添加一个虚拟的右括号，其位置索引为 -1
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st({ -1 });  // 仅用于记录第一个无效的右括号，以及左括号 ( 的位置
        int max_length = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);  // 弹出了最左侧的无效右括号，则将当前的右括号，置为新的无效边界
                } else {
                    max_length = max(max_length, i - st.top());
                }
            }
        }
        return max_length;
    }
};
}

namespace S3 {
// 32. 最长有效括号
// 计数，与使用栈的思想类似，但通过计数完成，以避免额外空间开销
// 使用 left 和 right 分别表示左括号和右括号的数目；当新出现一个多余右括号时，则左侧统计的所有信息都无法再使用，两数都置 0
// 新的左括号使 left 自增，新的右括号使 right 自增，当构成有效子序列时，一定是 left 与 right 相等，此时更新最长序列长度
// 但这种方法无法统计 (() 的情况，因为 right 没有机会与 left 相等；为此，我们再从最右侧向最左侧统计一遍即可
class Solution {
public:
    int longestValidParentheses(string s) {
        int max_length = 0;
        int left = 0, right = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') left++;
            else right++;
            if (left > right) {
                continue;
            } else if (left == right) {
                max_length = max(max_length, 2 * left);
            } else /* right > left */ {
                left = right = 0;  // 出现多余的右括号
            }
        }
        left = 0, right = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == ')') right++;
            else left++;
            if (left < right) {
                continue;
            } else if (left == right) {
                max_length = max(max_length, 2 * right);
            } else /* right < left */ {
                left = right = 0;  // 出现多余的左括号
            }
        }
        return max_length;
    }
};
}