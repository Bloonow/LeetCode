#include <vector>
using namespace std;

namespace S1 {
// 39. 组合总和
class Solution {
public:
    const int MAX_NUMBER = 150;
    void combine(vector<vector<int>>& rets, vector<int>& seq, vector<int>& candidates, int first, int sum, int target) {
        if (seq.size() >= MAX_NUMBER || sum > target) return;  // 超出边界条件
        if (sum == target) {
            rets.emplace_back(seq.begin(), seq.end());
            return;
        }
        for (int i = first; i < candidates.size(); i++) {
            int value = candidates[i];
            if (sum + value > target) continue;
            seq.push_back(value);
            sum += value;
            combine(rets, seq, candidates, i, sum, target);
            seq.pop_back();
            sum -= value;
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> rets({});
        vector<int> seq;
        combine(rets, seq, candidates, 0, 0, target);
        return rets;
    }
};
}