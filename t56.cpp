#include <stack>
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
// 对于答案的列表中每一个项，不断追加新的元素
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