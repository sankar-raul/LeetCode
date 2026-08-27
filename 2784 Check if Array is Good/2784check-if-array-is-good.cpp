class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size() - 1;
        int actualSum = n * (n + 1) / 2;
        int sum = 0;
        int prev = -1;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (prev == nums[i] && i < n) {
                return false;
            }
            prev = nums[i];
        }
        return sum - actualSum == n;
    }
};