#include <vector>
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
// 94. 二叉树的中序遍历
class Solution {
public:
    vector<int> Traversal(TreeNode *bt) {
        vector<int> rets;
        const int FIRST = 1, SECOND = 2;
        stack<pair<TreeNode*, int>> stack;
        stack.push({ bt, FIRST });
        while (!stack.empty()) {
            auto frame = stack.top(); stack.pop();
            TreeNode *node = frame.first;
            int count = frame.second;
            if (node == nullptr) continue;  // do nothing
            if (count == FIRST) {
                // 按照前序遍历、中序遍历、后序遍历的顺序要求，以相反的顺序入栈
                // 此处以中序遍历为示例
                stack.push({ node->right, FIRST });
                stack.push({ node, SECOND });
                stack.push({ node->left, FIRST });
            } else {
                // count == SECOND
                // 在此处执行访问操作
                rets.push_back(node->val);
            }
        }
        return rets;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> rets = Traversal(root);
        return rets;
    }
};
}

namespace S2 {
struct BTNode {
    int value;
    BTNode *left;
    BTNode *right;
};
void Traversal(BTNode *bt) {
    const int FIRST = 1, SECOND = 2, THIRD = 3;
    stack<pair<BTNode*, int>> stack;
    stack.push({ bt, FIRST });
    while (!stack.empty()) {
        auto frame = stack.top(); stack.pop();
        BTNode *node = frame.first;
        int count = frame.second;
        if (node == nullptr) continue;  // do nothing
        switch (count) {
        case FIRST:
            // 第一次遍历到该节点，刚从父节点指过来；若是前序遍历，则在此处执行访问操作
            stack.push({ node, SECOND });       // 第一次遍历结束，入栈以被第二次遍历
            stack.push({ node->left, FIRST });  // 左孩子入栈，以确保下个节点遍历其左孩子
            break;
        case SECOND:
            // 第二次遍历到该节点，刚从左孩子返回来；若是中序遍历，则在此处执行访问操作
            stack.push({ node, THIRD });         // 第二次遍历结束，入栈以被第三次遍历
            stack.push({ node->right, FIRST });  // 右孩子入栈，以确保下个节点遍历其右孩子
            break;
        case THIRD:
        default:
            // 第三次遍历到该节点，刚从右孩子返回来；若是后序遍历，则在此处执行访问操作
            // 第三次遍历结束，左右孩子、当前节点均被遍历完成，无需任何操作
            break;
        }
    }
}
}

namespace S3 {
struct BTNode {
    int value;
    BTNode *left;
    BTNode *right;
};
void Traversal(BTNode *bt) {
    const int FIRST = 1, SECOND = 2;
    stack<pair<BTNode*, int>> stack;
    stack.push({ bt, FIRST });
    while (!stack.empty()) {
        auto frame = stack.top(); stack.pop();
        BTNode *node = frame.first;
        int count = frame.second;
        if (node == nullptr) continue;  // do nothing
        if (count == FIRST) {
            // 按照前序遍历、中序遍历、后序遍历的顺序要求，以相反的顺序入栈
            // 此处以中序遍历为示例
            stack.push({ node->right, FIRST });
            stack.push({ node, SECOND });
            stack.push({ node->left, FIRST });
        } else {
            // count == SECOND
            // 在此处执行访问操作
        }
    }
}
}