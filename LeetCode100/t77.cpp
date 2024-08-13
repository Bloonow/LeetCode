#include <vector>
#include <cstdint>
using namespace std;

// 121. 买卖股票的最佳时机
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = INT32_MAX;
        int max_profix = INT32_MIN;
        for (const int& v : prices) {
            min_price = min(min_price, v);
            max_profix = max(max_profix, v - min_price);
        }
        return max_profix;
    }
};