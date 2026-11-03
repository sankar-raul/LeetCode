class Solution {
public:
    void backtrace(int idx, int n, vector<int>& nums, vector<int>& subset, vector<vector<int>>& res) {
        if (idx == n) return;
        
        backtrace(idx+1, n, nums, subset, res);
        subset.push_back(nums[idx]);
        res.push_back(subset);
        backtrace(idx+1, n, nums, subset, res);
        subset.pop_back();
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res(1);
        vector<int> subset;
        backtrace(0, nums.size(), nums, subset, res);
        return res;
    }
};