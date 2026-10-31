class Solution {
public:
    const int MOD = 1e9 + 7;
    int m, n;
    int countPath(int i, int j, vector<vector<int>>& grid, int direction, vector<vector<vector<int>>>& dp) { // direction { 1 for down | 2 for right }
        if (i == m - 1 && j == n - 1) {
            return 1;
        }
        if (i == m || j == n) {
            return 0;
        }
        if (dp[i][j][0] != -1) {
            return dp[i][j][0];
        }
        if (dp[i][j][direction] != -1) {
            return dp[i][j][direction];
        };
        int total_paths = 0;
        if (grid[i][j] == 0) {
            int right = countPath(i, j + 1, grid, 2, dp);
            int down = countPath(i + 1, j, grid, 1, dp);
            total_paths = (right + down) % MOD;
        } else {
            if (direction == 2) {  // reflect to down 😊
                total_paths = countPath(i + 1, j, grid, 1, dp);
                return dp[i][j][2] = total_paths; 
            } else { // reflect to right
                total_paths = countPath(i, j + 1, grid, 2, dp);
                return dp[i][j][1] = total_paths; 
            }
        }
        return dp[i][j][0] = total_paths;
    }
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, -1))); // {empty_cell, down_ray, right_ray}
        return countPath(0, 0, grid, 1, dp);
    }
};