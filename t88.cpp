#include <vector>
#include <cstdint>
using namespace std;

namespace S1 {
// 152. 乘积最大子数组
// 动态规划，用前缀和，不用判断正数和负数的情况
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product = INT32_MIN;
        int idx = 0;
        while (idx < nums.size() && nums[idx] == 0) {
            max_product = max(max_product, 0);
            idx++;  // 找到第一个非零数
        }
        while (idx < nums.size()) {
            // 处理一连串非零数组
            vector<double> prefix({ 1 });  // 一个案例刚好存在 int64_t 无法存储的情况
            while (idx < nums.size() && nums[idx] != 0) {
                prefix.push_back(prefix.back() * nums[idx]);
                if (prefix.back() > 0) {
                    max_product = max((double)max_product, prefix.back());
                } else {
                    for (int i = 0; i < prefix.size() - 1; i++) {
                        max_product = max((double)max_product, prefix.back() / prefix[i]);
                    }
                }
                idx++;
            }
            // 找到下一串的第一个非零数
            while (idx < nums.size() && nums[idx] == 0) {
                max_product = max(max_product, 0);
                idx++;
            }
        }
        return max_product;
    }
};
}

namespace S2 {
// 152. 乘积最大子数组
// 动态规划，不用前缀和，分正数和负数两种情况判断；正数之积要尽可能大，负数之积要尽可能小
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 一个案例刚好存在 int64_t 无法存储的情况
        double cur_max = nums[0], cur_min = nums[0], prev_max = nums[0], prev_min = nums[0];
        double ret_value = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cur_max = max((double)(nums[i]), max(prev_max * nums[i], prev_min * nums[i]));
            cur_min = min((double)(nums[i]), min(prev_max * nums[i], prev_min * nums[i]));
            prev_max = cur_max;
            prev_min = cur_min;
            ret_value = max(cur_max, ret_value);
        }
        return ret_value;
    }
};
}

namespace S3 {
// 152. 乘积最大子数组
// 设一个不包含 0 的序列，对于其连续乘积最大值所构成的子序列，一定以原序列的开头位置，或结尾位置，作为端点，这是因为（反证法）
// 如果连续乘积最大值子序列不以开头或结尾作为端点，也就是说，子序列两边都有非 0 的整数，那么分类讨论，
// (1) 如果连续乘积最大值为正，那么结果序列左右两边应该异号，否则可以向两边扩展；
// 而如果两边异号，那么一定存在一边为正，也可以继续扩展，与假设矛盾；
// (2) 如果连续乘积最大值为负，那么结果序列两边一定同号，否则一定一正一负，可以向两边扩展：
// (2.1) 如果同负，那么乘以任意一个负数都会让乘积变大；(2.2)如果同正，那么任意一个正数都大于这个负数的连续乘积最大值。
// 综上，不以起点开始且不以终点结束的序列，一定不是最大的连续乘积
// 于是，可从左向右一遍，再从右向左一遍，常规动态规划即可
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 一个案例刚好存在 int64_t 无法存储的情况
        double max_value = nums[0];
        double product = 1;
        for (int i = 0; i < nums.size(); i++) {
            product *= nums[i];
            max_value = max(product, max_value);
            if (nums[i] == 0) {
                product = 1;
            }
        }
        product = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            product *= nums[i];
            max_value = max(product, max_value);
            if (nums[i] == 0) {
                product = 1;
            }
        }
        return max_value;
    }
};
}