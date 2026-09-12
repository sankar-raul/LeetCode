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
    vector<vector<int>> res;
    void dfs(TreeNode* root, int targetSum, int sum, vector<int> path) {
        if (!root) return;
        sum += root->val;
        path.push_back(root->val);
        if (sum == targetSum && !root->left && !root->right) {
            res.push_back(path);
            return;
        }
        dfs(root->left, targetSum, sum, path);
        dfs(root->right, targetSum, sum, path);
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum, 0, {});
        return res;
    }
};