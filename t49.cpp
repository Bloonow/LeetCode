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

// 236. 二叉树的最近公共祖先
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 后序，先找到其中一个节点 p，然后判断 p 及其祖先当中，是否存在到达 q 的路径
        bool find_p = false, find_q = false;
        TreeNode *cur = root;
        TreeNode *last_visit = nullptr;
        stack<TreeNode*> st;
        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                st.push(cur);
                if (cur->val == p->val) {
                    find_p = true; break;
                } else if (cur->val == q->val) {
                    find_q = true; break;
                } else {
                    cur = cur->left;
                }
            } else {
                // 已经处于最左下角
                cur = st.top();
                if (cur->right != nullptr && cur->right != last_visit) {
                    cur = cur->right;  // 转向栈顶节点右孩子
                } else {
                    // 栈顶节点的左右孩子都访问过
                    st.pop();
                    last_visit = cur;
                    cur = nullptr;
                }
            }
        }
        TreeNode *has_find, *need_find;
        if (find_p) {
            has_find = p; need_find = q;
        } else if (find_q) {
            has_find = q; need_find = p;
        }
        // 接下来寻找另一个，后序，为避免重复寻找，使用 last_visit 标识上一次寻找的子树
        cur = st.top();
        last_visit == nullptr;
        stack<TreeNode*> st_find;
        while (cur != nullptr || !st_find.empty() || !st.empty()) {
            if (cur != nullptr) {
                st_find.push(cur);
                if (cur->val == need_find->val) break;
                if (cur->left != last_visit) {
                    cur = cur->left;
                } else {
                    last_visit = cur;
                    cur = nullptr;
                }
            } else {
                // 已经处于最左下角，或者左孩子已经访问过
                cur = st_find.top();
                if (cur->val == need_find->val) break;
                if (cur->right != nullptr && cur->right != last_visit) {
                    cur = cur->right;
                } else {
                    // 栈顶节点的左右孩子都访问过
                    st_find.pop();
                    last_visit = cur;
                    cur = nullptr;
                    if (st_find.empty()) {
                        st.pop();
                        st_find.push(st.top());
                    }
                }
            }
        }
        return st.top();
    }
};