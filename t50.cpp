#include <cstdint>
#include <utility>
#include <algorithm>
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

// 124. 二叉树中的最大路径和
class Solution {
public:
    pair<int, int> find_max(TreeNode *node) {
        // <left_max_sequence, right_max_sequence, max_sequence>
        if (node == nullptr) return make_pair(0, INT32_MIN);
        auto [left_max_to_this, left_max_sequence] = find_max(node->left);
        auto [right_max_to_this, right_max_sequence] = find_max(node->right);
        left_max_to_this = max(node->val, left_max_to_this + node->val);
        right_max_to_this = max(node->val, right_max_to_this + node->val);
        int max_sequence = max(
            left_max_to_this + right_max_to_this - node->val,
            max(left_max_sequence, right_max_sequence)
        );
        return make_pair(max(left_max_to_this, right_max_to_this), max_sequence);
    }
    int maxPathSum(TreeNode* root) {
        auto ret = find_max(root);
        return ret.second;
    }
};