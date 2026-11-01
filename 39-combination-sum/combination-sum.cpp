class Solution {
public:
    void comb(vector<int>& candidates, int i, int sum, int &target, vector<int>& path, vector<vector<int>>& res) {
        if (sum >= target) {
            cout << sum << endl;
            if (sum == target) {
                res.push_back(path);
            }
            return;
        }
        if (candidates.size() == i) return;
        path.push_back(candidates[i]);
        comb(candidates, i, sum + candidates[i], target, path, res);
        path.pop_back();
        comb(candidates, i + 1, sum, target, path, res);
        return;

    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        comb(candidates, 0, 0, target, path, res);
        return res;
    }
};