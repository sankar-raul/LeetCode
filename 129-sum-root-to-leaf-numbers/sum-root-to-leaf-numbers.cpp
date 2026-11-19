/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int dfs(TreeNode* root, int path_sum) {
        if (!root) return 0;
        path_sum = path_sum * 10 + root->val;
        if (!root->left && !root->right) {
            return path_sum;
        }
        return dfs(root->left, path_sum) + dfs(root->right, path_sum);
    }
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
};