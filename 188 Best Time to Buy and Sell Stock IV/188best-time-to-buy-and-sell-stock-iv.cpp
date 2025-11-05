class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        // If k is large enough, it's the same as unlimited transactions
        if (k >= n / 2) {
            int profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] > prices[i - 1])
                    profit += prices[i] - prices[i - 1];
            return profit;
        }

        vector<vector<int>> dp(k + 1, vector<int>(n, 0));

        for (int t = 1; t <= k; ++t) {
            int maxDiff = -prices[0];
            for (int i = 1; i < n; ++i) {
                dp[t][i] = max(dp[t][i - 1], prices[i] + maxDiff);
                maxDiff = max(maxDiff, dp[t - 1][i] - prices[i]);
            }
        }

        return dp[k][n - 1];
    }
};
