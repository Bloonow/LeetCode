#include <vector>
#include <queue>
#include <string>
using namespace std;

namespace S1 {
// 17. 电话号码的字母组合
class Solution {
public:
    vector<vector<char>> mp;  // <number, alphabet>
    Solution() {
        mp.resize('9' - '2' + 1);  // 个数
        mp['2' - '2'] = { 'a', 'b', 'c' };
        mp['3' - '2'] = { 'd', 'e', 'f' };
        mp['4' - '2'] = { 'g', 'h', 'i' };
        mp['5' - '2'] = { 'j', 'k', 'l' };
        mp['6' - '2'] = { 'm', 'n', 'o' };
        mp['7' - '2'] = { 'p', 'q', 'r', 's' };
        mp['8' - '2'] = { 't', 'u', 'v' };
        mp['9' - '2'] = { 'w', 'x', 'y', 'z' };
    }
    int number_has_chars(char number) {
        return mp[number - '2'].size();
    }
    char number_get_char(char number, int index) {
        return mp[number - '2'][index];
    }
    void combine(vector<string>& rets, string& digits, string& target, int num, int length) {
        if (num == length) {
            rets.push_back(target);  // 全部数字对应的字母组合完毕，保存当前解
            return;
        }
        for (int idx = 0; idx < number_has_chars(digits[num]); idx++) {
            target[num] = number_get_char(digits[num], idx);
            combine(rets, digits, target, num + 1, length);
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};
        vector<string> rets;
        string target_string;
        target_string.resize(digits.size());
        combine(rets, digits, target_string, 0, digits.size());
        return rets;
    }
};
}

namespace S2 {
// 17. 电话号码的字母组合
// 逐层动态构造
class Solution {
public:
    vector<vector<char>> mp;  // <number, alphabet>
    Solution() {
        mp.resize('9' - '2' + 1);  // 个数
        mp['2' - '2'] = { 'a', 'b', 'c' };
        mp['3' - '2'] = { 'd', 'e', 'f' };
        mp['4' - '2'] = { 'g', 'h', 'i' };
        mp['5' - '2'] = { 'j', 'k', 'l' };
        mp['6' - '2'] = { 'm', 'n', 'o' };
        mp['7' - '2'] = { 'p', 'q', 'r', 's' };
        mp['8' - '2'] = { 't', 'u', 'v' };
        mp['9' - '2'] = { 'w', 'x', 'y', 'z' };
    }
    int number_has_chars(char number) {
        return mp[number - '2'].size();
    }
    char number_get_char(char number, int index) {
        return mp[number - '2'][index];
    }
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};
        queue<string> q; q.push("");
        for (int handle = 0; handle < digits.size(); handle++) {
            int cur_num = q.size();
            while(cur_num--) {
                string tmp = q.front(); q.pop();
                for (int idx = 0; idx < number_has_chars(digits[handle]); idx++) {
                    q.push(tmp + number_get_char(digits[handle], idx));
                }
            }
        }
        vector<string> rets;
        while (!q.empty()) {
            rets.push_back(q.front()); q.pop();
        }
        return rets;
    }
};
}