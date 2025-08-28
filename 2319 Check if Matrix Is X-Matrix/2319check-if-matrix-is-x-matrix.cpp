class Solution {
public:
    int sum(vector<int> arr, vector<int> except, int n) {
        for (int i = 0; i < n; i++) {
            if (i != except[0] && i != except[1]) {
                if (arr[i] != 0) return false;
            }
        }
        return true;
    }
    bool checkXMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            if (grid[i][i] != 0 && grid[i][n-i-1] != 0) {
                int isZeros = sum(grid[i], {i, n - i - 1}, n);
                if (!isZeros) return false; 
            } else {
                return false;
            }
        }
        return true;
    }
};