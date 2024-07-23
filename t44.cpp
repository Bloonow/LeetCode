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

// 230. 二叉搜索树中第K小的元素
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stack;
        TreeNode *p = root;
        int cur = 0;
        while (p != nullptr || !stack.empty()) {
            while (p != nullptr) {
                stack.push(p);
                p = p->left;
            }
            p = stack.top(); stack.pop();
            cur++;  // 遍历第 cur 小的数据
            if (cur == k) return p->val;
            p = p->right;
        }
        return -1;
    }
};