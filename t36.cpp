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
// 递归实现
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> rets;
        if (root->left != nullptr) {
            auto next_ret = inorderTraversal(root->left);
            rets.insert(rets.end(), next_ret.begin(), next_ret.end());
        }
        rets.push_back(root->val);
        if (root->right != nullptr) {
            auto next_ret = inorderTraversal(root->right);
            rets.insert(rets.end(), next_ret.begin(), next_ret.end());
        }
        return rets;
    }
};
}

namespace S2 {
// 94. 二叉树的中序遍历
// 非递归实现之一
class Solution {
public:
    vector<int> Traversal(TreeNode *bt) {
        vector<int> rets;
        const int FIRST = 1, SECOND = 2, THIRD = 3;
        stack<pair<TreeNode*, int>> stack;
        stack.push({ bt, FIRST });
        while (!stack.empty()) {
            auto frame = stack.top(); stack.pop();
            TreeNode *node = frame.first;
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
                rets.push_back(node->val);
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
        return rets;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> rets = Traversal(root);
        return rets;
    }
};
}

namespace S3 {
// 94. 二叉树的中序遍历
// 非递归实现之二
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

namespace S4 {
// 94. 二叉树的中序遍历
// 非递归实现之三
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> rets;
        stack<TreeNode*> stack;
        TreeNode *p = root;
        while (p != nullptr || !stack.empty()) {
            if (p != nullptr) {
                stack.push(p);
                p = p->left;
            } else {
                p = stack.top(); stack.pop();
                rets.push_back(p->val);
                p = p->right;
            }
        }
        return rets;
    }
};
}

namespace S5 {
// 94. 二叉树的中序遍历
// Morris遍历算法是另一种遍历二叉树的方法，它能将非递归的中序遍历空间复杂度降为O(1)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *p = root;
        while (p != nullptr) {
            if (p->left != nullptr) {
                // prev 节点就是当前 p 节点向左走一步，然后一直向右走至无法走为止
                TreeNode *prev = p->left;
                while (prev->right != nullptr && prev->right != p) {
                    prev = prev->right;
                }
                // 让 prev 的右指针指向 p，继续遍历左子树
                if (prev->right == nullptr) {
                    prev->right = p;
                    p = p->left;
                } else {
                    // 说明左子树已经访问完了，我们需要断开链接
                    res.push_back(p->val);
                    prev->right = nullptr;
                    p = p->right;
                }
            } else {
                // 如果没有左孩子，也属于左子树已经遍历完成，则执行访问操作，然后访问右孩子
                res.push_back(p->val);
                p = p->right;
            }
        }
        return res;
    }
};
}