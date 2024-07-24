#include <vector>
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

// 105. 从前序与中序遍历序列构造二叉树
class Solution {
public:
    TreeNode* create(vector<int>& preorder, vector<int>& inorder, int preLeft, int preRight, int inLeft, int inRight) {
        if (preLeft > preRight || inLeft > inRight) return nullptr;
        if (preLeft == preRight || inLeft == inRight) return new TreeNode(preorder[preLeft]);
        int this_value = preorder[preLeft];
        int in_index = find(inorder.begin() + inLeft, inorder.begin() + inRight + 1, this_value) - inorder.begin();
        int left_node_num = in_index - inLeft;
        int right_node_num = inRight - in_index;
        return new TreeNode(
            this_value,
            create(preorder, inorder, preLeft + 1, preLeft + left_node_num, inLeft, in_index - 1),
            create(preorder, inorder, preRight - right_node_num + 1, preRight, in_index + 1, inRight)
        );
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};