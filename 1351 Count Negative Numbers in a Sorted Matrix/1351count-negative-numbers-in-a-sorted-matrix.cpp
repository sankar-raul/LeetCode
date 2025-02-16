class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int n = grid.size(), count = 0;
        int low, high, mid;
        for (int i = 0; i < n; i++) {
            low = 0;
            high = grid[i].size() - 1;
            while (low <= high) {
                mid = low + (high - low) / 2;
                if (grid[i][mid] >= 0) {
                    low = mid + 1;
                } else {
                    count += grid[i].size() - mid;
                    int left = mid - 1;
                    while (left >= low && grid[i][left] < 0) {
                        count++;
                        left--;
                    }
                    break;
                }
            }
        }
        return count;
    }
};