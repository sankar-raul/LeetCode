class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        if (n == 1) return nums[0];
        for (int i = 1; i < n; ++i) {
            nums[i] += nums[i-1];
        }
        int mini = 1e9;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= r - l && i + l + j - 1 < n; ++j) {
                int sum = nums[i + l + j - 1] - (i ? nums[i-1] : 0);
                if (sum > 0 && sum < mini) {
                    mini = sum;
                }
            }
        }
        return mini == 1e9 ? -1 : mini;
    }
};