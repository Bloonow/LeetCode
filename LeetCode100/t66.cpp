#include <vector>
using namespace std;

// 33. 搜索旋转排序数组
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;  // 初始时，i、j 落在两个段上
        int mid, bound_left, bound_right;
        while (i <= j && nums[i] > nums[j]) {
            mid = (i + j) / 2;
            if (mid == i) {
                // 只存在两个有效元素
                bound_left = i;
                bound_right = j;
                break;
            } else if (nums[mid] < nums[mid - 1]) {
                // 在边界处
                bound_left = mid - 1;
                bound_right = mid;
                break;
            } else if (nums[mid] > nums[mid + 1]) {
                // 在边界处
                bound_left = mid;
                bound_right = mid + 1;
                break;
            } else {
                // 缩放范围
                if (nums[mid] > nums[i]) {
                    i = mid + 1;  // 较大的区域
                } else /* nums[mid] < nums[i] */ {
                    j = mid - 1;  // 较小的区域
                }
            }
        }
        int k = bound_right;
        if (target == nums[k]) {
            return k;
        } else if (target < nums[0]) {
            i = k, j = nums.size() - 1;
        } else /* target > nums[0] */ {
            i = 0, j = k - 1;
        }
        while (i <= j) {
            mid = (i + j) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
        return -1;
    }
};
