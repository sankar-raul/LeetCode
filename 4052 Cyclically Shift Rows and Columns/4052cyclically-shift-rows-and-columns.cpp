class Solution {
public:
    vector<vector<int>> cyclicShift(int n, vector<vector<int>>& grid, vector<int>& rowShift, vector<int>& colShift) {
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            vector<int>& row = grid[i];
            int k;
            for (int j = n - 1; j >= 0; --j) {
                k = (j - rowShift[i] + n) % n;
                ans[i][k] = row[j];
            }
        }
    
        for (int i = 0; i < n; ++i) {
            int k;
            for (int j = n - 1; j >= 0; --j) {
                k = (j - colShift[i] + n) % n;
                grid[k][i] = ans[j][i];
            }
        }
        return grid;
    }
};