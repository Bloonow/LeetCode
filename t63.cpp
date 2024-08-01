#include <vector>
using namespace std;

namespace S1 {
// 35. 搜索插入位置
class Solution {
public:
    int binary_search(vector<int>& nums, int target, int i, int j) {
        while (i <= j) {
            int mid = (i + j) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                return binary_search(nums, target, mid + 1, j);
            } else {
                return binary_search(nums, target, i, mid - 1);
            }
        }
        return i;
    }
    int searchInsert(vector<int>& nums, int target) {
        return binary_search(nums, target, 0, nums.size() - 1);
    }
};
}

namespace S2 {
// 35. 搜索插入位置
// 非递归方式
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        while (i <= j) {
            int mid = (i + j) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                i = mid + 1;
            } else {
                j = mid - 1;
            }
        }
        return i;
    }
};
}