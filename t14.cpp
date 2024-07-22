#include <vector>
#include <algorithm>
using namespace std;

// 56. 合并区间
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> rets;
        sort(intervals.begin(), intervals.end());  // 默认即按左端点排序
        int left = intervals[0][0], right = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= right) {
                right = max(right, intervals[i][1]);
            } else {
                rets.push_back({left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        rets.push_back({left, right});
        return rets;
    }
};