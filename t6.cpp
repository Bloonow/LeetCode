#include <vector>
#include <algorithm>
using namespace std;

// 15. 三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> rets;
        int length = nums.size();
        sort(nums.begin(), nums.end());
        for (int baseIdx = 0; baseIdx < length; baseIdx++) {
            if (baseIdx > 0 && nums[baseIdx] == nums[baseIdx - 1]) continue;  // 已分析，跳过
            int target = 0 - nums[baseIdx];
            int i = baseIdx + 1, j = length - 1;
            while (i < j) {
                if (nums[i] + nums[j] > target) {
                    j--;
                } else if (nums[i] + nums[j] < target) {
                    i++;
                } else {
                    // nums[i] + nums[j] == target
                    if ((baseIdx + 1 == i && j == length - 1) || 
                        (nums[i] != nums[i - 1]) || (nums[j] != nums[j + 1])
                    ) {
                        rets.push_back({nums[baseIdx], nums[i], nums[j]});
                    }
                    i++; j--;
                }
            }
        }
        return rets;
    }
};