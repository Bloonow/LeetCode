#include <cstdint>
#include <unordered_map>
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

// 437. 路径总和 III
// 先遍历一遍二叉树，求从根节点到下面节点的前缀和，然后，即是求 pre[j] - pre[i] == target
// 设 i < j，其中 i, j 能够分别表示所对应节点所在的层数，于是，在使用 j 遍历二叉树时，
// 寻找满足 pre[j] - pre[i] == target 的索引 i 的数目，使用哈希表来存储，以供下侧的孩子节点查找
class Solution {
public:
    int scan_count(
        TreeNode *node, unordered_map<int64_t, int64_t>& mp, int64_t targetSum, int64_t prefix
    ) {
        if (node == nullptr) return 0;
        int count = 0;
        prefix = prefix + node->val;
        int64_t need = prefix - targetSum;
        if (mp.find(need) != mp.end()) {
            count += mp[need];
        }
        mp[prefix]++;
        count += scan_count(node->left, mp, targetSum, prefix);
        count += scan_count(node->right, mp, targetSum, prefix);
        mp[prefix]--;
        return count;
    }
    int pathSum(TreeNode* root, int64_t targetSum) {
        unordered_map<int64_t, int64_t> mp;  // need, times
        int64_t prefix = 0;
        mp[0] = 1;  // 处理当 need = prefix - targetSum = 0，也即 prefix == targetSum 的情况
        int count = scan_count(root, mp, targetSum, prefix);
        return count;
    }
};