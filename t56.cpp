#include <vector>
#include <algorithm>
using namespace std;

namespace S1 {
// 78. 子集
class Solution {
public:
    void subset_helper(vector<vector<int>>& rets, vector<int>& nums, vector<int>& seq, int select, int N) {
        // 选 1 个、2 个、3 个、...
        if (select >= N) return;
        seq.push_back(nums[select]);
        rets.emplace_back(seq.begin(), seq.end());
        for (int idx = select; idx < N; idx++) {
            subset_helper(rets, nums, seq, idx + 1, N);
        }
        seq.pop_back();
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> rets({ {} });  // 空集
        vector<int> seq;
        for (int i = 0; i < nums.size(); i++) {
            subset_helper(rets, nums, seq, i, nums.size());
        }
        return rets;
    }
};
}

namespace S2 {
// 78. 子集
// 组合问题，可以采用回溯法，也可以逐层动态构造，即对于答案的列表中每一个项，不断追加新的元素
// 设存在 N 个位置，每个位置上可以有 num[i] 种候选项，则将其组合时，可以逐层动态构造
// { [1,2], [3,4,5], [6,7] }
// 即，从 i = 0 --> N-1 迭代过程中，逐步考察，将 i 位置上的所有 num[i] 个候选项加入当前答案 rets 中所有部分答案之后的情况
// 若最终每个答案的长度固定为 N，则每次考察 i 位置上的所有候选项时，需要先将当前答案中的所有部分答案移除
// {} --> { [1], [2] } --> { [1,3], [1,4], [1,5], [2,3], [2,4], [2,5] } -->
// { [1,3,6], [1,3,7], [1,4,6], [1,4,7], [1,5,6], [1,5,7], [2,3,6], [2,3,7], ... }
// 若长度不固定，则无需移除原有的部分答案；若每个位置仅有一个候选项，则可以少一层循环
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> rets({ {} });  // 空集
        // 追加 value 的值
        for (const int& value : nums) {
            int numbers = rets.size();
            for (int i = 0; i < numbers; i++) {
                rets.emplace_back(rets[i].begin(), rets[i].end());
                rets.back().push_back(value);
            }
        }
        return rets;
    }
};
}