#include <vector>
using namespace std;

namespace S1 {
// 198. 打家劫舍
class Solution {
public:
    int rob(vector<int>& nums) {
        int length = nums.size();
        if (length == 1) return nums[0];
        if (length == 2) return max(nums[0], nums[1]);
        if (length == 3) return max(nums[1], nums[0] + nums[2]);
        vector<int> dp(length);
        dp[0] = nums[0]; dp[1] = nums[1]; dp[2] = nums[0] + nums[2];
        for (int i = 3; i < length; i++) {
            dp[i] = max(dp[i - 3], dp[i - 2]) + nums[i];
        }
        return max(dp[length - 1], dp[length - 2]);
    }
};
}

namespace S2 {
// 198. 打家劫舍
// 因为最终状态只与前几个状态相关，所以可以使用滚动数组，避免额外空间开销
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int first = nums[0];
        int second = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            int temp = max(first + nums[i], second);
            first = second;
            second = temp;
        }
        return second;
    }
};
}

