class Solution {
public:
    void backtrace(int idx, int n, vector<int>& nums, vector<int>& seq, vector<bool>& seen, vector<vector<int>>& res) {
        if (idx == n) {
            res.push_back(seq);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!seen[i]) {
                seen[i] = true;
                seq.push_back(nums[i]);
                backtrace(idx+1, n, nums, seq, seen, res);
                seq.pop_back();
                seen[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> seen(nums.size());
        vector<vector<int>> res;
        vector<int> seq;
        backtrace(0, nums.size(), nums, seq, seen, res);
        return res;
    }
};