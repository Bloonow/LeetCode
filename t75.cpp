#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// 347. 前 K 个高频元素
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counts;  // 记录每个值出现的次数
        for (const auto& v : nums) {
            counts[v]++;
        }
        auto comp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
            return a.second > b.second;  // 用于自定义优先级队列，小值优先级更高
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);  // 小根堆
        for (const auto& kv : counts) {
            if (q.size() == k) {
                if (q.top().second < kv.second) {
                    q.pop();
                    q.push(kv);
                }
            } else {
                q.push(kv);
            }
        }
        vector<int> rets;
        while (!q.empty()) {
            rets.push_back(q.top().first);
            q.pop();
        }
        return rets;
    }
};
