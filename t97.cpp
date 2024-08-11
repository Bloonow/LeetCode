#include <vector>
using namespace std;

// 169. 多数元素
// Boyer-Moore 投票算法
// 基于一个事实：如果一个数组有大于一半的数相同，那么任意删去两个不同的数字，新数组还是会有相同的性质
// 同归于尽消杀法：
// 由于多数超过50%, 比如100个数，那么多数至少51个，剩下少数至多49个
// 第一个到来的士兵，直接插上自己阵营的旗帜占领这块高地，此时领主 winner 就是这个阵营的人，现存兵力 count = 1
// 如果新来的士兵和前一个士兵是同一阵营，则集合起来占领高地，领主不变，winner 依然是当前这个士兵所属阵营，现存兵力 count++
// 如果新来到的士兵不是同一阵营，则前方阵营派一个士兵和它同归于尽，此时前方阵营兵力count--，
//     即使双方都死光，这块高地的旗帜 winner 依然不变，因为已经没有活着的士兵可以去换上自己的新旗帜
// 当下一个士兵到来，发现前方阵营已经没有兵力，新士兵就成了领主，winner 变成这个士兵所属阵营的旗帜，现存兵力 count++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = -1;
        int count = 0;
        for (const int& value : nums) {
            if (candidate == value) {
                count++;
            } else {
                count--;
                if (count < 0) {
                    candidate = value;
                    count = 1;
                }
            }
        }
        return candidate;
    }
};