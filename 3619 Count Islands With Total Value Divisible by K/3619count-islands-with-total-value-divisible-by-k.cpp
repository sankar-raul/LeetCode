class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        queue<pair<int, int>> q;
        int islands = 0, m = grid.size(), n = grid[0].size();

        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                if (!grid[x][y]) continue;
                q.push({x, y});
                long long sum = grid[x][y];
                grid[x][y] = 0;
                while (q.size()) {
                    auto [i, j] = q.front();
                    q.pop();
                    if (j+1 < n && grid[i][j+1]) {
                        q.push({i, j+1});
                        sum += grid[i][j+1];
                        grid[i][j+1] = 0;
                    }
                    if (j && grid[i][j-1]) {
                        q.push({i, j-1});
                        sum += grid[i][j-1];
                        grid[i][j-1] = 0;
                    }
                    if (i+1 < m && grid[i+1][j]) {
                        q.push({i+1, j});
                        sum += grid[i+1][j];
                        grid[i+1][j] = 0;
                    }
                    if (i && grid[i-1][j]) {
                        q.push({i-1, j});
                        sum += grid[i-1][j];
                        grid[i-1][j] = 0;
                    }
                }
                if (sum % k == 0) {
                    islands++;
                }
            }
        }
        return islands;
    }
};