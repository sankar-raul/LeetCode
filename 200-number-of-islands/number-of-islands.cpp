class Solution {
public:
    int m, n;
    void is_island(int i, int j, vector<vector<char>>& grid) {
        if (i < 0 || j < 0 || i == m || j == n || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        is_island(i+1, j, grid);
        is_island(i-1, j, grid);
        is_island(i, j+1, grid);
        is_island(i, j-1, grid);
    }
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(), n = grid[0].size();
        int islands = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    islands++;
                    is_island(i, j, grid);
                }
            }
        }
        return islands;
    }
};