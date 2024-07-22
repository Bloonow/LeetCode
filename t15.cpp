#include <vector>
using namespace std;

// 189. 轮转数组
// 双逆序法
class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        int i = start, j = end;
        int tmp;
        while (i < j) {
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
            i++; j--;
        }
    }
    void rotate(vector<int>& nums, int k) {
        int length = nums.size();
        k %= length;  // 防止循环多轮
        reverse(nums, 0, length - k - 1);
        reverse(nums, length - k, length - 1);
        reverse(nums, 0, length - 1); 
    }
};