#include <vector>
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

// 102. 二叉树的层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) return {};
        vector<vector<int>> rets;
        rets.push_back({});
        int curCount = 0;
        int curTotalCount = 1;
        int nextTotalCount = 0;
        queue<TreeNode*> q({ root });
        while (!q.empty()) {
            if (curCount == curTotalCount) {
                // 新的一层
                rets.push_back({});
                curCount = 0;
                curTotalCount = nextTotalCount;
                nextTotalCount = 0;
            } else {
                TreeNode *p = q.front(); q.pop();
                curCount++;
                if (p->left != nullptr) {
                    q.push(p->left);
                    nextTotalCount++;
                }
                if (p->right != nullptr) {
                    q.push(p->right);
                    nextTotalCount++;
                }
                rets.back().push_back(p->val);
            }
        }
        return rets;
    }
};