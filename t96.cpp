#include <vector>
using namespace std;

namespace S1 {
// 136. 只出现一次的数字
//         1 <= nums.length <= 3 * 10^4
// -3 * 10^4 <= nums[i]     <= 3 * 10^4
// 使用常量的额外空间，只能重用原来的 nums 数组
// 遍历数组，对于一个数字 x，使用 nums[x] 存储其是否出现过，但又不能丢失原位置上的信息
// 【答案错误】地址越界
class Solution {
public:
    void set_mask(int& value, int pos) {
        int mask = 1;
        for (int i = 0; i < pos; i++) mask *= 10;
        mask = value >= 0 ? mask : -mask;
        value += mask;
    }
    void del_mask(int& value, int pos) {
        int mask = 1;
        for (int i = 0; i < pos; i++) mask *= 10;
        mask = value >= 0 ? mask : -mask;
        value -= mask;
    }
    bool get_mask(int& value, int pos) {
        int mask = 1;
        for (int i = 0; i < pos; i++) mask *= 10;
        int left = (value / (mask * 10)) * (mask * 10);
        int right = value % mask;
        mask = value >= 0 ? mask : -mask;
        return value - left - right == mask ? true : false;
    }
    int singleNumber(vector<int>& nums) {
        int length = nums.size();
        nums.push_back(0);    // 用于处理 abs == 3 * 10^4 的情况
        for (int i = 0; i < length; i++) {
            int x = nums[i];  // 在 x 位置上设置掩码
            int pos = x >= 0 ? 6 : 7;
            if (get_mask(nums[x], pos)) {
                del_mask(nums[x], pos);
            } else {
                set_mask(nums[x], pos);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (get_mask(nums[i], 6)) {
                return i;
            } else if (get_mask(nums[i], 7)) {
                return -i;
            } else {
                continue;
            }
        }
        return -1;
    }
};
}

namespace S2 {
// 136. 只出现一次的数字
// 用异或操作，异或运算有以下三个性质
// (1) 任何数和 0 做异或运算，结果仍然是原来的数，即 a⊕0=a
// (2) 任何数和其自身做异或运算，结果是 0，即 a⊕a=0
// (3) 异或运算满足交换律和结合律，即 a⊕b⊕a=b⊕a⊕a=b⊕(a⊕a)=b⊕0=b
// 因此，数组中的全部元素的异或运算结果即为数组中只出现一次的数字
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (const int& value : nums) ret ^= value;
        return ret;
    }
};
}