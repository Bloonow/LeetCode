#include <vector>
using namespace std;

// 31. 下一个排列
// 将最后一个处于递增序列上的数值，向前移动一位，并将之后的序列，排列为递增序
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1) return;
        int top = nums.size() - 1;
        // 寻找最右侧一段的降序序列，这一段序列无法再凭借自身增大，只能向左借一位之后，才能继续增大
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] >= nums[i + 1]) {
                top = i;
            } else {
                break;
            }
        }
        if (top == nums.size() - 1) {
            swap(nums[top], nums[top - 1]);
            return;
        }
        if (top == 0) {
            // 整个序列为递降序列，颠倒之
            int i = 0, j = nums.size() - 1;
            while (i < j) {
                swap(nums[i++], nums[j--]);
            }
            return;
        }
        int idx = top;  // 从降序序列当中，选取一个比 nums[top - 1] 更大且最小的数字，左移
        while (idx + 1 <= nums.size() - 1 && nums[idx + 1] > nums[top - 1]) idx++;
        swap(nums[top - 1], nums[idx]);
        // 将原来的降序序列，改为最小状态的升序
        int i = top, j = nums.size() - 1;
        while (i < j) {
            swap(nums[i++], nums[j--]);
        }
    }
};