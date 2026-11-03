class Solution {
public:
    void backtrace(int idx, int n, int sum, int target, vector<int>& path, vector<int>& candidates, vector<vector<int>>& res) {
        if (idx == n || sum + candidates[idx] > target) {
            if (sum == target) res.push_back(path);
            return;
        }
        int next = idx;
        while (next < n-1) {
            if (candidates[idx] == candidates[++next]) continue;
            if (candidates[next] + sum > target) break;
            backtrace(next, n, sum, target, path, candidates, res);
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