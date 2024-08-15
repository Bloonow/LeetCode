#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 108. 将有序数组转换为二叉搜索树
class Solution {
public:
    TreeNode* create(vector<int>& nums, int left, int right) {
        if (left == right) {
            return new TreeNode(nums[left]);
        } else if (left + 1 == right) {
            return new TreeNode(nums[right], new TreeNode(nums[left]), nullptr);
        } else {
            int mid = (left + right + 1) / 2;
            return new TreeNode(nums[mid], create(nums, left, mid - 1), create(nums, mid + 1, right));
        }
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.size() == 0) return nullptr;
        return create(nums, 0, nums.size() - 1);
    }
};