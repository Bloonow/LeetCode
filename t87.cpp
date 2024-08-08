#include <vector>
#include <map>
#include <algorithm>
using namespace std;

namespace S1 {
// 300. 最长递增子序列
// 动态规划，最坏情形下，O(N^2) 时间复杂度
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int max_length = 1;
        map<int, int, greater<int>> mp;  // 一个数，该数最后一次出现的索引，降序
        vector<int> dp(nums.size(), 1);  // 元素 dp[i] 表示序列 nums[0...i] 中，以 nums[i] 结尾所能构成的最长子序列
        for (int i = 0; i < nums.size(); i++) {
            int the_value = nums[i];
            auto iter = find_if(mp.begin(), mp.end(), [&the_value](const pair<int, int>& item) {
                return item.first < the_value;  // 寻找第一个小于 nums[i] 的值，并不是二分，😭 sad
            });
            if (iter == mp.end()) {
                // 不存在小于 nums[i] 的值，表示 nums[i] 是当前最小的值，无法跟之前的序列构成递增序列
                dp[i] = 1;
            } else {
                // 存在比 nums[i] 小的值，因为 mp 是降序，故之后的值都是小于 nums[i] 的值，判断是否能构成更长序列
                for (; iter != mp.end(); iter++) {
                    dp[i] = max(dp[i], dp[iter->second] + 1);
                }
            }
            mp[nums[i]] = i;
            max_length = max(max_length, dp[i]);
        }
        return max_length;
    }
};
}

namespace S2 {
// 300. 最长递增子序列
// 动态规划，代码简洁一些
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
}

namespace S3 {
// 300. 最长递增子序列
// 贪心算法，二分查找
// 在寻找严格递增子序列时，为使得递增序列长度最长，则每次递增的增量不能太大，
// 可以说，每次递增的增量越小，其所能够取得的最长递增子序列的长度，就有可能越长
// 使用一个数组 seq[i] 表示，所构造的长度为 i 的递增序列，最后一个元素的值，
// 例如，seq{N} 表示，长度为 N 的递增序列，其最后一个值是 seq[N-1]；
// 从左到右遍历原序列，构造 seq 数组，数组 seq 各个元素之间的值，没有任何联系；在遍历过程中，
// (1) 如果一个新的值 value，大于 seq 序列的最后一个值，则直接将新的值放在最后，表示又找到一个新值构造递增子序列
// (2) 如果一个新的值 value，小于等于 seq{N} 序列中的最后一个值 seq[N-1]，则说明新的值，无法构成长度为 N 及更长的序列，
// 但可以构成长度更短的序列，且增量最小，于是在数组 seq 中寻找 seq[j] < value < seq[i]，并令 seq[i] = value
// 表示，构成长度为 i 的自增子序列时，序列最后一个元素的值应该是 value，如此保证增量最小；
// (3) 最有用的情况是，一个新的值 value，其符合 seq[N-2] < value < seq[N-1]，此时更新 seq[N-1] = value，
// 即更新能够构成长度为 N 的最长子序列的最后一个值，如此可以保证，将来可以更有可能构成更长的递增子序列
class Solution {
public:
    int find_first_greater_equal_index(const vector<int>& ordered_sequence, int value) {
        int i = 0, j = ordered_sequence.size() - 1;
        while (i <= j) {
            int m = (i + j) / 2;
            if (value == ordered_sequence[m]) {
                return m;
            } else if (value < ordered_sequence[m]) {
                j = m - 1;
            } else {
                i = m + 1;
            }
        }
        return i;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> seq({ nums[0] });
        for (int i = 1; i < nums.size(); i++) {
            if (seq.back() < nums[i]) {
                seq.push_back(nums[i]);
            } else {
                int idx = find_first_greater_equal_index(seq, nums[i]);
                seq[idx] = nums[i];
            }
        }
        return seq.size();
    }
};
}