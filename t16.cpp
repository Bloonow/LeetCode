#include <vector>
using namespace std;

namespace S1 {
// 238. 除自身以外数组的乘积
// 使用前缀和扫描 prefix_sum_scan
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> prefix(length);
        vector<int> suffix(length);
        vector<int> rets(length);
        prefix[0] = nums[0];
        suffix[length - 1] = nums[length - 1];
        for (int i = 1; i < length; i++) {
            prefix[i] = prefix[i - 1] * nums[i];
            suffix[length - i - 1] = suffix[length - i] * nums[length - i - 1];
        }
        rets[0] = suffix[1];
        rets[length - 1] = prefix[length - 2];
        for (int i = 1; i < length - 1; i++) {
            rets[i] = prefix[i - 1] * suffix[i + 1];
        }
        return rets;
    }
};
}

namespace S2 {
// 238. 除自身以外数组的乘积
// 使用前缀和扫描 prefix_sum_scan，使用结果数组临时保存 prefix_sum_scan
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int length = nums.size();
        vector<int> rets(length);
        rets[0] = nums[0];
        for (int i = 1; i < length; i++) {
            rets[i] = rets[i - 1] * nums[i];  // 此处获得前缀和 rets
        }
        int suffix = nums[length - 1];        // 后缀和
        rets[length - 1] = rets[length - 2];  // 最后一个位置已就位
        for (int j = length - 2; j >= 1; j--) {
            rets[j] = rets[j - 1] * suffix;
            suffix = suffix * nums[j];    // 更新后缀和
        }
        rets[0] = suffix;
        return rets;
    }
};
}