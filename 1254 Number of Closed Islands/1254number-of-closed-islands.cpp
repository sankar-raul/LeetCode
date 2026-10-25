class Solution {
public:
    int m,n;
    bool dfs(int i, int j, vector<vector<int>> &grid) {
        if (i < 0 || j < 0 || i == m || j == n) return false;
        if (grid[i][j] == 1) return true;
        grid[i][j] = 1; // mark as visited
        bool right = dfs(i, j + 1, grid);
        bool left = dfs(i, j - 1, grid);
        bool down = dfs(i+1, j, grid);
        bool up = dfs(i-1, j, grid);
        return right && left && down && up;
    }
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int ilands = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    bool can = dfs(i, j, grid);
                    ilands += can;
                }
            }
        }
        return ilands;
    }
};