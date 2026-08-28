class Solution {
public:
    int tribonacci(int n) {
        int dp[] = {0, 1, 1};
        if (n < 3) {
            return dp[n];
        }
        for (int i = 3; i <= n; ++i) {
            int nth_tib = dp[0] + dp[1] + dp[2];
            dp[0] = dp[1];
            dp[1] = dp[2];
            dp[2] = nth_tib;
        }
        return dp[2];
    }
};