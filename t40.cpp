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

// 543. 二叉树的直径
class Solution {
public:
    pair<int, int> recurs(TreeNode *tn) {
        // <max_diameter, max_depth>
        if (tn->left == nullptr && tn->right == nullptr) return make_pair(0, 1);
        int left_diameter = 0, left_depth = 0;
        if (tn->left != nullptr) {
            auto ret = recurs(tn->left);
            left_diameter = ret.first;
            left_depth = ret.second;
        }
        int right_diameter = 0, right_depth = 0;
        if (tn->right != nullptr) {
            auto ret = recurs(tn->right);
            right_diameter = ret.first;
            right_depth = ret.second;
        }
        int cur_depth = max(left_depth, right_depth) + 1;
        int cur_diameter = max(left_depth + right_depth, max(left_diameter, right_diameter));
        return make_pair(cur_diameter, cur_depth);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        auto ret = recurs(root);
        return ret.first;
    }
};