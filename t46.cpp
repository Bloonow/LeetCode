#include <utility>
#include <stack>
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

namespace S1 {
// 114. 二叉树展开为链表
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        if (root->left == nullptr) {
            flatten(root->right);
            return;
        }
        TreeNode *left = root->left;
        TreeNode *left_last = left;
        while (left_last->right != nullptr) left_last = left_last->right;
        left_last->right = root->right;
        root->right = left;
        root->left = nullptr;
        flatten(root->right);
    }
};
}

namespace S2 {
// 114. 二叉树展开为链表
// 如何使用非递归方式实现？
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        TreeNode *curr = root;
        while (curr != nullptr) {
            if (curr->left != nullptr) {
                TreeNode *prev = curr->left;
                while (prev->right != nullptr) {
                    prev = prev->right;
                }
                prev->right = curr->right;
                curr->right = curr->left;
                curr->left = nullptr;
            }
            curr = curr->right;
        }
    }
};
}