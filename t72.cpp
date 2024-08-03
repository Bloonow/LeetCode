#include <vector>
#include <stack>
using namespace std;

// 739. 每日温度
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        if (temperatures.size() == 0) return {};
        vector<int> rets; rets.resize(temperatures.size());
        stack<int> stack;
        int cur = 0;
        while (cur < temperatures.size()) {
            if (stack.empty()) {
                stack.push(cur);
                cur++;
            } else {
                // 栈不为空，则表示存在前一天的数据，与前一天比较
                int prev = stack.top();
                if (temperatures[prev] >= temperatures[cur]) {
                    // 温度没有升高，则继续入栈
                    stack.push(cur);
                    cur++;
                } else {
                    // 温度已然升高，设置前几天的状态，并继续向前几天遍历
                    rets[prev] = cur - prev;
                    stack.pop();
                }
            }
        }
        return rets;
    }
};