class Solution {
public:
    void backtrace(int idx, int n, vector<int>& candidates, vector<int>& seq, int sum, int& target, vector<vector<int>>& res) {
        if (idx == n || sum >= target) {
            if (sum == target) res.push_back(seq);
            return;
        }
        int next = idx + 1;
        while (next < n && candidates[idx] == candidates[next]) next++;
        if (next < n && candidates[next] + sum <= target) backtrace(next, n, candidates, seq, sum, target, res);
        
        seq.push_back(candidates[idx]);
        backtrace(idx+1, n, candidates, seq, sum + candidates[idx], target, res);
        seq.pop_back();
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> seq;

        backtrace(0, candidates.size(), candidates, seq, 0, target, res);

        return res;
    }
};