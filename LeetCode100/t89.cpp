#include <vector>
#include <unordered_set>
#include <numeric>
#include <algorithm>
using namespace std;

namespace S1 {
// 416. 分割等和子集
// 深度搜索，分支限界法
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 1) return false;
        int all_sum = accumulate(nums.begin(), nums.end(), 0);
        if (all_sum % 2 == 1) return false;
        // 若能划分成两个集合，并保证集合元素之和相等，则总和一定为偶数
        int target = all_sum / 2;  // 问题转化为，找到若干元素，使这些元素构成的和为 target
        unordered_set<int> st;  // 在考虑一个新的元素后，已经可以构造的值
        for (const int value : nums) {
            if (value > target) {
                continue;
            } else if (value == target) {
                return true;
            } else /* value < target */ {
                unordered_set<int> new_st;
                for (const int has_value : st) {
                    if (has_value + value > target) {
                        continue;
                    } else if (has_value + value == target) {
                        return true;
                    } else /* has_value + value < target */ {
                        new_st.insert(has_value + value);
                    }
                }
                st.insert(value);
                st.insert(new_st.begin(), new_st.end());
            }
        }
        return false;
    }
};
}

namespace S2 {
// 416. 分割等和子集
// 动态规划
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 1) return false;
        int all_sum = accumulate(nums.begin(), nums.end(), 0);
        if (all_sum % 2 == 1) return false;
        // 若能划分成两个集合，并保证集合元素之和相等，则总和一定为偶数
        int target = all_sum / 2;  // 问题转化为，找到若干元素，使这些元素构成的和为 target
        vector<int> dp(1 + target, false);  // 不要用 <boo>，比 <int> 慢很多
        dp[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            // 逐个考虑元素，判断能够构成的新的状态
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};
}