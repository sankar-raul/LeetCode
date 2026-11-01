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
    void dfs(TreeNode* root, vector<TreeNode*>& st) {
        if (!root) return;
        st.push_back(root);
        dfs(root->left, st);
        dfs(root->right, st);
    }
    void flatten(TreeNode* root) {
        if (!root) return;
        vector<TreeNode*> st;
        dfs(root, st);
        TreeNode *prev = st[0];
        prev->left = nullptr;
        for (int i = 1; i < st.size(); ++i) {
            st[i]->left = nullptr;
            prev->right = st[i];
            prev = st[i];
        }
    }
};