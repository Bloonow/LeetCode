#include <vector>
using namespace std;

namespace S1 {
// 3152. 特殊数组 II
// 直接动态规划，内存超限，需要优化
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int length = nums.size();
        vector<vector<int>> dp(length, vector<int>(length, 0));  // 元素 dp[i][j] 表示数组 nums[i...j] 是否符合
        for (int i = 0; i < length; i++) dp[i][i] = 1;
        for (int len = 2; len <= length; len++) {
            for (int i = 0; i < length - len; i++) {
                if (dp[i][i + len - 2] == 1 && (nums[i + len - 2] % 2) != (nums[i + len - 1] % 2)) {
                    dp[i][i + len - 1] = 1;
                }
            }
        }
        vector<bool> rets(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            rets[i] = dp[queries[i][0]][queries[i][1]];
        }
        return rets;
    }
};
}

namespace S2 {
// 3152. 特殊数组 II
// 问题具有最优子结构性质，在数组 nums 中一定存在若干段子数组，满足条件，找出最长的这些子数组并记录
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        vector<pair<int, int>> range;
        int start = 0;
        while (start < nums.size()) {
            int end = start + 1;
            while (end < nums.size()) {
                if (nums[end - 1] % 2 != nums[end] % 2) {
                    end++;
                } else {
                    break;
                }
            }
            range.emplace_back(start, end - 1);
            start = end;
        }
        vector<bool> rets(queries.size());
        for (int idx = 0; idx < queries.size(); idx++) {
            int start = queries[idx][0], end = queries[idx][1];
            // 二分查找
            int i = 0, j = range.size() - 1;
            while (i <= j) {
                int m = (i + j) / 2;
                if (range[m].first == start) {
                    j = m; i = m + 1;
                } else if (range[m].first > start) {
                    j = m - 1;
                } else /* range[m].first < start */ {
                    i = m + 1;
                }
            }
            if (range[j].first <= start && end <= range[j].second) {
                rets[idx] = true;
            } else {
                rets[idx] = false;
            }
        }
        return rets;
    }
};
}