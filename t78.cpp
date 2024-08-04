#include <vector>
using namespace std;

// 55. 跳跃游戏
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int jump_length = nums[0];
        if (jump_length == 0 && nums.size() == 1) return false;
        for (int i = 1; i < nums.size(); i++) {
            jump_length--;
            jump_length = max(jump_length, nums[i]);
            if (jump_length == 0 && i != nums.size() - 1) return false;
        }
        return true;
    }
};