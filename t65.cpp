#include <vector>
using namespace std;

// 34. 在排序数组中查找元素的第一个和最后一个位置
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) return { -1, -1 };
        int i = 0, j = nums.size() - 1, mid;
        while (i <= j) {
            mid = (i + j) / 2;
            if (nums[mid] == target) {
                break;
            } else if (target < nums[mid]) {
                j = mid - 1;
            } else /* nums[mid] < target */ {
                i = mid + 1;
            }
        }
        if (nums[mid] != target) return { -1, -1 };  // 未找到匹配
        // 已找到匹配，现在寻找左右边界，不能直接遍历，否则对于全部相等数列而言，时间复杂度为 O(N)
        int left = i, right = j;  // 目标 target 所构成的范围，一定处于 [left, right] 当中
        int find_index = mid;     // 第一次匹配到的索引
        i = left, j = find_index - 1;  // 向左侧寻找，左侧数据只会小于等于 target
        while (i <= j) {
            mid = (i + j) / 2;
            if (nums[mid] == target) {
                j = mid - 1;
            } else /* nums[mid] < target */ {
                i = mid + 1;
            }
        }
        int start = i;
        i = find_index + 1, j = right;  // 向右侧寻找，右侧数据只会大于等于 target
        while (i <= j) {
            mid = (i + j) / 2;
            if (nums[mid] == target) {
                i = mid + 1;
            } else /* target < nums[mid] */ {
                j = mid - 1;
            }
        }
        int last = j;
        return { start, last };
    }
};