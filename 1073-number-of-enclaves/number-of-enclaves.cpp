class Solution {
public:
    int dfs(int i, int j, int m, int n, vector<vector<int>>& grid, bool& has_boundary) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) return 0;
        if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
            has_boundary = true;
        }
        grid[i][j] = 0;
        return 1 + dfs(i-1, j, m, n, grid, has_boundary) + dfs(i+1, j, m, n, grid, has_boundary) + dfs(i, j-1, m, n, grid, has_boundary) + dfs(i, j+1, m, n, grid, has_boundary);
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int count = 0, m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    bool has_boundary = false;
                    int cnt = dfs(i, j, m, n, grid, has_boundary);
                    if (!has_boundary)
                        count += cnt;
                }
            }
        }
        return count;
    }
};