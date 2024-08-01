#include <vector>
#include <string>
using namespace std;

// 22. 括号生成
// 🧡🧡 ✌🥵✌ 🧡🧡
class Solution {
public:
    void backtrack(vector<string>& rets, string seq, int can_left, int can_right) {
        if (can_left <= 0) {
            if (can_right > 0) seq.insert(seq.end(), can_right, ')');
            rets.push_back(seq);
            return;
        }
        // 尝试插入右括号
        if (can_right > 0) {
            string new_seq(seq);
            new_seq.insert(new_seq.end(),')');
            backtrack(rets, new_seq, can_left, can_right - 1);
        }
        // 尝试插入左括号
        if (can_left > 0) {
            string new_seq(seq);
            new_seq.insert(new_seq.end(), '(');
            backtrack(rets, new_seq, can_left - 1, can_right + 1);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> rets;
        string seq;
        backtrack(rets, seq, n, 0);
        return rets;
    }
};
