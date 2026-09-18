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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> q;
        vector<long long> levelSums;
        q.push(root);
        while (!q.empty()) {
            long long sum = 0;
            int level_size = q.size();
            while (level_size--) {
                TreeNode* node = q.front();
                sum += node->val;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
                q.pop();
            }
            levelSums.push_back(sum);
        }
        if (k > levelSums.size()) return -1;
        sort(levelSums.begin(), levelSums.end());
        return levelSums[levelSums.size() - k];
    }
};