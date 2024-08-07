#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

// 322. 零钱兑换
// 不能从最大的开始凑
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());  // 先排一下序，其实排不排无所谓
        vector<int> dp(amount + 1, 0);     // dp[i] 表示兑成 i 所需的最少硬币的个数，使用虚拟边界 dp[0] = 0;
        for (int target = 1; target <= amount; target++) {
            int min_kinds = INT32_MAX;
            for (const int& val : coins) {
                if (target - val >= 0 && dp[target - val] != INT32_MAX) {
                    min_kinds = min(min_kinds, dp[target - val] + 1);
                }
            }
            dp[target] = min_kinds;
        }
        return dp[amount] != INT32_MAX ? dp[amount] : -1;
    }
};