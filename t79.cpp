#include <vector>
using namespace std;

// 45. 跳跃游戏 II
// 贪心，假设可以从当前 index 跳到 target_index，那么，也可以跳到 [index + 1, target_index] 之间的任意位置
// 依次判断，选择在 [index + 1, target_index] 之间的，可以使下一次跳跃位置最大的一个索引，作为该次跳跃的目标
class Solution {
public:
    int jump(vector<int>& nums) {
        int jump_step = 0;
        int cur_index = 0;
        while (cur_index < nums.size() - 1) {
            jump_step++;
            int target_index = cur_index + nums[cur_index];
            if (target_index >= nums.size() - 1) break;
            int max_next_index = target_index;
            int max_next_position = target_index + nums[target_index];
            for (int i = cur_index + 1; i < target_index; i++) {
                if (i + nums[i] > max_next_position) {
                    max_next_index = i;
                    max_next_position = i + nums[i];
                }
            }
            cur_index = max_next_index;
        }
        return jump_step;
    }
};