class Solution {
public:
    void backtrace(int idx, int n, int sum, int target, vector<int>& path, vector<int>& candidates, vector<vector<int>>& res) {
        if (idx == n || sum + candidates[idx] > target) {
            if (sum == target) res.push_back(path);
            return;
        }
        for (int i = idx; i < n; ++i) {
            if (candidates[idx] == candidates[i]) continue;
            backtrace(i, n, sum, target, path, candidates, res);
            break;
        }
        path.push_back(candidates[idx]);
        backtrace(idx+1, n, sum + candidates[idx], target, path, candidates, res);
        path.pop_back();
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> path;
        vector<vector<int>> res;
        sort(candidates.begin(), candidates.end());
        backtrace(0, candidates.size(), 0, target, path, candidates, res);
        return res;
    }
};