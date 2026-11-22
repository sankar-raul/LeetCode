class Solution {
public:
    int backtrace(int i, int j, int m, int n, vector<vector<int>>& grid,
                  int free_cell, int count) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == -1) {
            return 0;
        }
        if (grid[i][j] == 2) {
            return free_cell == count - 1;
        }
        int prev = grid[i][j];
        grid[i][j] = -1;
        int total = backtrace(i + 1, j, m, n, grid, free_cell, count + 1) +
                    backtrace(i - 1, j, m, n, grid, free_cell, count + 1) +
                    backtrace(i, j + 1, m, n, grid, free_cell, count + 1) +
                    backtrace(i, j - 1, m, n, grid, free_cell, count + 1);
        grid[i][j] = prev;
        return total;
    }
    int uniquePathsIII(vector<vector<int>>& grid) {
        pair<int, int> start_cell;
        int free_cell = 0, m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    free_cell++;
                } else if (grid[i][j] == 1) {
                    start_cell = {i, j};
                }
            }
        }
        return backtrace(start_cell.first, start_cell.second, m, n, grid,
                         free_cell, 0);
    }
};