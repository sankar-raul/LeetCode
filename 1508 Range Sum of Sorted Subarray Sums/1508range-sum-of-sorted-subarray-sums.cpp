class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        vector<long long> sums;
        long long ans = 0;
        long long MOD =  1'000'000'007LL;
        for (int i = 0; i < nums.size(); ++i) {
            long long curr_sum = 0;
            for (int j = i; j < nums.size(); ++j) {
                sums.push_back(curr_sum += nums[j]);
            }
        }
        sort(sums.begin(), sums.end());
        for (int i = left - 1; i < right; ++i) {
            ans += sums[i];
        }
        return ans % MOD;
    }
};