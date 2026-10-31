class Solution {
public:
    const int MOD = 1e9 + 7;
    int m, n;
    int countPath(int i, int j, vector<vector<int>>& grid, int direction, vector<vector<pair<int, int>>>& dp) { // direction { 0 for down | 1 for right }
        if (i == m - 1 && j == n - 1) {
            return 1;
        }
        if (i == m || j == n) {
            return 0;
        }
        if (dp[i][j].first != -1 || dp[i][j].second != -1) {
            auto& [ down, right ] = dp[i][j];
            int count_for_direction = direction == 0 ? down : right;
            if (grid[i][j] == 0) {
                return (down + right) % MOD;
            } else if (count_for_direction != -1) {
                return count_for_direction;
            }
        }
        int total_paths = 0;
        if (grid[i][j] == 0) {
            int right = countPath(i, j + 1, grid, 1, dp);
            dp[i][j].second = right;
            int down = countPath(i + 1, j, grid, 0, dp);
            dp[i][j].first = down;
            total_paths = (right + down) % MOD;
        } else {
            if (direction == 1) {  // reflect to down 😊
                dp[i][j].second = countPath(i + 1, j, grid, 0, dp); 
                return dp[i][j].second;
            } else { // reflect to right
                dp[i][j].first = countPath(i, j + 1, grid, 1, dp);
                return dp[i][j].first;
            }
        }
        return total_paths;
    }
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        vector<vector<pair<int, int>>> dp(m, vector<pair<int, int>>(n, {-1, -1})); // {empty_cell, down_ray, right_ray}
        return countPath(0, 0, grid, 1, dp);
    }
};