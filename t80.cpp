#include <string>
#include <vector>
#include <set>
using namespace std;

namespace S1 {
// 763. 划分字母区间
// 从左到右依次遍历，每遍历到一个新的字母，则向右寻找该字母出现的最后一个位置，这是所能划分的最小位置
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> rets;
        int totals[26] = { 0 };  // 表示每个字母出现的总次数
        set<char> has_occurs;    // 记录在遍历过程中，左侧出现的字母种类
        for (const char& ch : s) {
            totals[ch - 'a']++;
        }
        int start = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];
            has_occurs.insert(ch);
            totals[ch - 'a']--;
            if (totals[ch - 'a'] == 0) {
                has_occurs.erase(ch);
            }
            if (has_occurs.empty()) {
                rets.push_back(i - start + 1);
                start = i + 1;
            }
        }
        return rets;
    }
};
}

namespace S2 {
// 763. 划分字母区间
// 贪心策略，在遍历过程中，动态维护可划分一段的最后一个位置，只有达到该位置，才能划分一段
class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> rets;
        int ends[26];  // 记录每个字母最后一次出现的位置
        for (int i = 0; i < s.length(); i++) {
            ends[s[i] - 'a'] = i;
        }
        int start = 0;               // 起始位置
        int end = ends[s[0] - 'a'];  // 应该结束的位置
        for (int i = 0; i < s.length(); i++) {
            end = max(end, ends[s[i] - 'a']);
            if (i == end) {
                rets.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return rets;
    }
};
}