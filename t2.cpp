#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 49. 字母异位词分组
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(), str.end());  // 将原字符串排序，以确定唯一键值
            mp[str].emplace_back(strs[i]);
        }
        vector<vector<string>> ret_strs;
        for (auto it = mp.begin(); it != mp.end(); it++) {
            ret_strs.emplace_back(it->second);
        }
        return ret_strs;
    }
};