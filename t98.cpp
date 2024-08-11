#include <vector>
using namespace std;

// 75. 颜色分类
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero_idx = 0;  // 下一个用于存放 0 的索引
        int one_idx = 0;   // 下一个用于存放 1 的索引
        for (int idx = 0; idx < nums.size(); idx++) {
            if (nums[idx] == 0) {
                nums[idx] = nums[one_idx];
                nums[one_idx] = nums[zero_idx];
                nums[zero_idx] = 0;
                zero_idx++;
                one_idx++;
            } else if (nums[idx] == 1) {
                nums[idx] = nums[one_idx];
                nums[one_idx] = 1;
                one_idx++;
            } else /* nums[idx] == 2 */ {
                continue;
            }
        }
    }
};