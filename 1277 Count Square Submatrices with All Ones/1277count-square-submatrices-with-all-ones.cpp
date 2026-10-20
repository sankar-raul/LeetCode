class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        int res = 0;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (matrix[i][j] == 0) continue;
                if (i + 1 == m || j + 1 == n) {
                    res += dp[i][j] = 1;
                    continue;
                }
                int maximum_posible_sq = 1 + min({dp[i][j+1], dp[i+1][j], dp[i+1][j+1]});
                res += dp[i][j] = maximum_posible_sq;
            }
        }
        return res;
    }
};