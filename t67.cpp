#include <vector>
using namespace std;

// 153. 寻找旋转排序数组中的最小值
class Solution {
public:
    int findMin(vector<int>& nums) {
        int mid, min_index = 0;
        int i = 1, j = nums.size() - 1;
        while (i <= j) {
            // 寻找分界点 k，满足 nums[k - i] > nums[k] 且 nums[k] < nums[k + i]
            mid = (i + j) / 2;
            if (nums[mid] > nums[0]) {
                i = mid + 1;
            } else /* nums[mid] <= nums[0] */ {
                min_index = mid;
                j = mid - 1;
            }
        }
        return nums[min_index];
    }
};