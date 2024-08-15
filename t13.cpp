#include <cstdint>
#include <vector>
using namespace std;

// 53. 最大子数组和
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur_subMax = nums[0];
        int global_max = cur_subMax;
        for (int i = 1; i < nums.size(); i++) {
            cur_subMax = max(cur_subMax + nums[i], nums[i]);
            global_max = max(global_max, cur_subMax);
        }
        return global_max;
    }
};