#include <vector>
#include <string>
#include <set>
using namespace std;

// 139. 单词拆分
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        set<int> length_set;  // 候选长度，以尽可能减少判断次数，有序集合
        for (const string& str : wordDict) length_set.insert(str.length());
        set<string> word_set;  // 字典，方便查找
        word_set.insert(wordDict.begin(), wordDict.end());
        // 字符串长度比字典中最短单词的长度还小，根本无法构成
        if (s.length() < *length_set.begin()) return false;
        vector<bool> dp(s.length());  // dp[i] 表示字符串 s[0...i] 可以由字典中的单词构成
        for (int idx = 0; idx < s.length(); idx++) {
            bool can_construct = false;
            for (const int& len : length_set) {
                // 逐个判断，是否能够由子串构成
                if (idx < len) {
                    can_construct = (word_set.find(s.substr(0, idx + 1)) != word_set.end());
                    break;  // 在逐个判断子串的过程中，子串长度已经超出，跳出
                } else if (dp[idx - len] && (word_set.find(s.substr(idx - len + 1, len)) != word_set.end())) {
                    can_construct = true;
                    break;
                } else {
                    continue;  // 继续判断下一个子串
                }
            }
            dp[idx] = can_construct;
        }
        return dp[s.length() - 1];
    }
};