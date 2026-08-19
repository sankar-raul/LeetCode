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
    void getPath(TreeNode* root, string path, vector<string>& res) {
        if (!root) {
            return;
        }
        if (path == "") {
            path += to_string(root->val);
        } else {
            path += "->" + to_string(root->val);
        }
        if (!root->left && !root->right) {
            res.push_back(path);
            return;
        }
        getPath(root->left, path, res);
        getPath(root->right, path, res);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        getPath(root, "", res);
        return res;
    }
};