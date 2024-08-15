#include <vector>
using namespace std;

// 118. 杨辉三角
// 你原来也是动态规划？
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> rets = { { 1 } };
        for (int row = 2; row <= numRows; row++) {
            int prev = row - 2;
            int index = row - 1;
            rets.push_back({});
            rets[index].push_back(1);
            for (int i = 1; i < row - 1; i++) {
                rets[index].push_back(rets[prev][i - 1] + rets[prev][i]);
            }
            rets[index].push_back(1);
        }
        return rets;
    }
};