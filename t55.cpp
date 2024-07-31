#include <vector>
#include <algorithm>
using namespace std;

// 46. 全排列
// 回溯法：一种通过探索所有可能的候选解来找出所有的解的算法。
// 如果候选解被确认不是一个解（或者至少不是最后一个解），回溯算法会通过在上一步进行一些变化抛弃该解，即回溯并且再次尝试。
class Solution {
public:
    void permute_fill(vector<vector<int>>& rets, vector<int>& sequence, int fill_index, int length) {
        // 从 fill_index 索引处开始，及其右侧元素，是待检索填充的，索引从 0 开始
        if (fill_index == length) {
            rets.emplace_back(sequence); return;
        }
        permute_fill(rets, sequence, fill_index + 1, length);  // 填充 fill_index 位置
        for (int i = fill_index + 1; i < length; i++) {
            // 从当前位置向后，依次填充剩余的可选元素，将已填充的元素放置 fill_index 位置，然后向后递归
            swap(sequence[fill_index], sequence[i]);
            permute_fill(rets, sequence, fill_index + 1, length);
            swap(sequence[fill_index], sequence[i]);  // 恢复状态
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> rets;
        permute_fill(rets, nums, 0, nums.size());
        return rets;
    }
};