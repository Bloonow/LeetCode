#include <vector>
using namespace std;

// 283. 移动零
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int num_zero = 0;
        int toAssignIdx = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (toAssignIdx < i) {
                    nums[toAssignIdx] = nums[i];
                    nums[i] = 0;
                }
                toAssignIdx++;
            }
        }
    }
};