class Solution {
public:
    const int MOD = 1e9 + 7;
    int m, n;
    int countPath(int i, int j, vector<vector<int>>& grid, int& count, char direction, vector<vector<vector<int>>>& dp) { // direction r | d
        if (i == m - 1 && j == n - 1) {
            count = (count + 1) % MOD;
            return 1;
        }
        if (i == m || j == n) {
            return 0;
        }
        if (dp[i][j][0] != -1) {
            count = (count + dp[i][j][0]) % MOD;
            return dp[i][j][0];
        }
        int direction_to_dp_index = direction == 'd' ? 1 : 2;
        if (dp[i][j][direction_to_dp_index] != -1) {
            count = (count + dp[i][j][direction_to_dp_index]) % MOD;
            return dp[i][j][direction_to_dp_index];
        };
        int total_paths = 0;
        if (grid[i][j] == 0) {
            int right = countPath(i, j + 1, grid, count, 'r', dp);
            int down = countPath(i + 1, j, grid, count, 'd', dp);
            total_paths = (right + down) % MOD;
        } else {
            if (direction == 'r') {  // reflect to down 😊
                total_paths = countPath(i + 1, j, grid, count, 'd', dp);
                return dp[i][j][2] = total_paths; 
            } else {
                total_paths = countPath(i, j + 1, grid, count, 'r', dp);
                return dp[i][j][1] = total_paths; 
            }
        }
        return dp[i][j][0] = total_paths;
    }
    int uniquePaths(vector<vector<int>>& grid) {
        int count = 0;
        m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(3, -1))); // {empty_cell, down_ray, right_ray}
        countPath(0, 0, grid, count, 'r', dp);
        return count;
    }
};