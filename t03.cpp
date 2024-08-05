#include <vector>
#include <unordered_set>
using namespace std;

// 128. 最长连续序列
// 所有数据可以构成若干个 x, x+1, x+2, ..., x+y 的连续序列，这些每个序列中的元素可分为两种：
// (1)序列的首个起始元素；(2)序列起始元素之后的连续元素。它们之间的区别在于，其左侧元素是否在原始序列当中
// 对于(1)的元素，依次从原序列中找右侧连续元素，累计长度；对于(2)中元素，它总能被左侧元素找到，跳过
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        st.insert(nums.begin(), nums.end());
        int longest = 0;
        for (auto it = st.begin(); it != st.end(); it++) {
            if (st.find(*it - 1) != st.end()) {
                continue;  // 存在左侧元素，跳过
            } else {
                int curLength = 1;
                int curVal = *it;
                for (;;) {
                    if (st.find(curVal + 1) != st.end()) {
                        // 存在右侧元素，累计长度
                        curLength++;
                        curVal++;
                    } else {
                        break;
                    }
                }
                longest = max(curLength, longest);
            }
        }
        return longest;
    }
};