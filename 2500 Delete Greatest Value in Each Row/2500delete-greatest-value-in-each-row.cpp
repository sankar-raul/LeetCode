class Solution {
public:
    int deleteGreatestValue(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        for (int i = 0; i < m; ++i) {
            sort(grid[i].begin(), grid[i].end());
        }
        for (int i = 0; i < n; ++i) {
            int max_val = 0;
            for (int j = 0; j < m; ++j) {
                max_val = max(max_val, grid[j][i]);
            }
            ans += max_val;
        }
        return ans;
    }
};