#include <cstdint>
#include <tuple>
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

// 98. 验证二叉搜索树
class Solution {
public:
    int64_t min(int64_t a, int64_t b, int64_t c) {
        int64_t temp = a < b ? a : b;
        return temp < c ? temp : c;
    }
    int64_t max(int64_t a, int64_t b, int64_t c) {
        int64_t temp = a < b ? b : a;
        return temp < c ? c : temp;
    }
    tuple<int64_t, int64_t, bool> minmax_check(TreeNode *node) {
        // <minimum, maximum>
        if (node == nullptr) return make_tuple(INT64_MAX, INT64_MIN, true);
        auto left_ret = minmax_check(node->left);
        auto right_ret = minmax_check(node->right);
        int64_t left_min = get<0>(left_ret);
        int64_t left_max = get<1>(left_ret);
        bool left_check = get<2>(left_ret);
        int64_t right_min = get<0>(right_ret);
        int64_t right_max = get<1>(right_ret);
        bool right_check = get<2>(right_ret);
        int64_t cur_min = min(node->val, left_min, right_min);
        int64_t cur_max = max(node->val, left_max, right_max);
        bool cur_check = left_check && right_check && left_max < node->val && node->val < right_min;
        return make_tuple(cur_min, cur_max, cur_check);
    }
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        if (root->left == nullptr && root->right == nullptr) return true;
        return get<2>(minmax_check(root));
    }
};