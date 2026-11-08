class Solution {
public:

    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> column(n);
        vector<int> row(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!grid[i][j]) continue;
                column[j]++;
                row[i]++;
            }
        }
        int count = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!grid[i][j]) continue;
                count += column[j] > 1 || row[i] > 1;
            }
        }
        return count;
    }
};