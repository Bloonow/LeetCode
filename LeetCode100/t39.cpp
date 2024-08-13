#include <queue>
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

// 101. 对称二叉树
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        TreeNode *lptr = root->left, *rptr = root->right;
        queue<TreeNode*> lq({ lptr }), rq({ rptr });
        while (!lq.empty() && !rq.empty()) {
            lptr = lq.front(); lq.pop();
            rptr = rq.front(); rq.pop();
            if (lptr == nullptr && rptr == nullptr) continue;
            if (lptr == nullptr && rptr != nullptr) return false;
            if (lptr != nullptr && rptr == nullptr) return false;
            if (lptr != nullptr && rptr != nullptr) {
                if (lptr->val != rptr->val) return false;
                lq.push(lptr->left); lq.push(lptr->right);
                rq.push(rptr->right); rq.push(rptr->left);
            }
        }
        if (!lq.empty() || !rq.empty()) return false;
        return true;
    }
};