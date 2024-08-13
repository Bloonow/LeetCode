#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

namespace S1 {
// 41. 缺失的第一个正数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int missing = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == missing) missing++;
        }
        return missing;
    }
};
}

namespace S2 {
// 41. 缺失的第一个正数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> st;
        for (int i = 0; i < nums.size(); i++) st.insert(nums[i]);
        int missing = 1;
        while (st.find(missing) != st.end()) {
            missing++;
        }
        return missing;
    }
};
}

namespace S3 {
// 41. 缺失的第一个正数
// 如何避免使用额外的哈希集合？
// 首先注意到，对于长度为N的数组来说，若其正好存储 [1, N] 中的所有正整数，则缺失的第一个正数将是 N+1，
// 否则但凡数组中出现其它元素，则第一个缺失正数将位于 [1, N] 范围，也即，缺失的第一个正数一定位于 [1, N+1] 范围
// 未避免使用额外的哈希集合，我们将原来的输入数组 nums 作为原地哈希的空间，显然的应该是：
// 若 nums[i] = x，表明出现过数据 x，将 nums[x-1] 处设置一个标记，以表示 x 出现过，现需要考虑如何避免覆盖 nums[x-1] 处的原数据
// 因为答案一定位于 [1, N+1] 范围内，且遍历一遍后，能得到的最大连续正整数是 N，则凡是负数均无作用，可以先将负数和零置为 N+1，
// 如此过后，数组中仅存在正整数，于是，我们可以采用整数的符号位作为标识，即，
// 对于一个数据 x，我们将 nums[x-1] 的符号位置为负数，用于标识数据 x 出现过，而此处原来的数据，又可以通过 abs(nums[x]) 获得
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int N = nums.size();
        for (int i = 0; i < N; i++) {
            if (nums[i] <= 0) nums[i] = N + 1;
        }
        int x;
        for (int i = 0; i < N; i++) {
            x = abs(nums[i]);
            if (x <= N) {
                // 1 <= x <= N
                nums[x - 1] = -abs(nums[x - 1]);
            }
        }
        int missing = 1;
        for (int i = 0; i < N; i++) {
            if (nums[i] < 0) {
                missing++;
            } else {
                return missing;
            }
        }
        return missing;
    }
};
}
