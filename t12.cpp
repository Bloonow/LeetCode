#include <string>
using namespace std;

namespace S1 {
// 76. 最小覆盖子串
class Solution {
public:
    static constexpr int NUM_CHAR = 52;
    bool cover(int sCnt[NUM_CHAR], int tCnt[NUM_CHAR]) {
        for (int i = 0; i < NUM_CHAR; i++) {
            if (sCnt[i] < tCnt[i]) return false;
        }
        return true;
    }
    int idx(char ch) {
        return (ch - 'A') - (ch / ('Z' + 1)) * ('a' - 'Z' - 1);
    }
    string minWindow(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        int sCnt[NUM_CHAR] = { 0 }, tCnt[NUM_CHAR] = { 0 };
        for (int i = 0; i < tLen; tCnt[idx(t[i++])]++);
        int global_left = -1, global_right = sLen;
        int left = 0, right = 0;
        for (right = 0; right < sLen; right++) {
            sCnt[idx(s[right])]++;  // 滑入新元素
            while (cover(sCnt, tCnt)) {
                // 子串已全部覆盖，则尝试收缩子串长度
                if (right - left < global_right - global_left) {
                    // 新子串长度更短
                    global_right = right;
                    global_left = left;
                }
                sCnt[idx(s[left++])]--;
            }
        }
        return global_left == -1 ? "" : s.substr(global_left, global_right - global_left + 1);
    }
};
}

namespace S2 {
// 76. 最小覆盖子串
// 上述方式判断是否覆盖时，每次都需要 NUM_CHAR 比较操作，如何使用一个标识来判断是否覆盖？
// 假设字符串 t 中共有若干种字符，使用整数 need 表示字符串 s 的子串还需要覆盖多少种字符，才能将字符串 t 完全覆盖
class Solution {
public:
    static constexpr int NUM_CHAR = 52;
    int idx(char ch) {
        return (ch - 'A') - (ch / ('Z' + 1)) * ('a' - 'Z' - 1);
    }
    string minWindow(string s, string t) {
        int sLen = s.length(), tLen = t.length();
        int sCnt[NUM_CHAR] = { 0 }, tCnt[NUM_CHAR] = { 0 };
        int need = 0;
        for (int i = 0; i < tLen; i++) {
            if (tCnt[idx(t[i])] == 0) need++;  // 该字母第一次出现
            tCnt[idx(t[i])]++;
        }
        int global_left = -1, global_right = sLen;
        int left = 0, right = 0;
        for (right = 0; right < sLen; right++) {
            sCnt[idx(s[right])]++;  // 滑入新元素
            if (sCnt[idx(s[right])] == tCnt[idx(s[right])]) need--;  // 若子串中某个字母的个数正好满足
            while (need == 0) {
                // 子串已全部覆盖，则尝试收缩子串长度
                if (right - left < global_right - global_left) {
                    // 新子串长度更短
                    global_right = right;
                    global_left = left;
                }
                // 若子串中某个字母的个数恰好满足，则移除后便不再满足
                if (sCnt[idx(s[left])] == tCnt[idx(s[left])]) need++;
                sCnt[idx(s[left])]--;
                left++;
            }
        }
        return global_left == -1 ? "" : s.substr(global_left, global_right - global_left + 1);
    }
};
}