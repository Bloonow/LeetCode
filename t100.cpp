#include <vector>
#include <math.h>
using namespace std;

namespace S1 {
// 287. 寻找重复数
// 因为数字都在 [1, n] 的范围内，故对于一个数字 x，可以使用 nums[x] 标识是否出现过
// 因为只有一个重复数字，可将原数字置为负值，标识已经出现过一次
// 但是修改数组了，如何不修改原数组呢？
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int value : nums) {
            value = abs(value);
            if (nums[value] < 0) {
                return value;
            } else {
                nums[value] = -nums[value];
            }
        }
        return -1;
    }
};
}

namespace S2 {
// 287. 寻找重复数
// 不修改原数组，将 nums 看成是一条链表 i --> nums[i]，因此仅存在一个重复数字，则链表中存在一个环
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            fast = nums[nums[fast]];
            slow = nums[slow];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            fast = nums[fast];
            slow = nums[slow];
        }
        return slow;
    }
};
}