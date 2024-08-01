#include <vector>
#include <string>
using namespace std;

// 131. 分割回文串
class Solution {
public:
    bool check(const string& s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++; j--;
        }
        return true;
    }
    void backtrack(vector<vector<string>>& rets, vector<string>& splits, const string& s, int first) {
        if (first >= s.length()) {
            rets.push_back(splits);
            return;
        }
        for (int num = 1; num <= s.length() - first; num++) {
            if (check(s, first, first + num - 1)) {
                // 当前子段是回文，记录之，并递归
                splits.push_back(s.substr(first, num));
                backtrack(rets, splits, s, first + num);
                splits.pop_back();  // 弹出之前的记录，转而判断更大的 num + 1 的情况
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> rets;
        vector<string> splits;
        backtrack(rets, splits, s, 0);
        return rets;
    }
};