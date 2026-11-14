class Solution {
public:
    int maxDigitRange(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        int sum = 0, max_range = 0;
        for (int i = 0; i < n; ++i) {
            int maxi = 0, mini = 9;
            int num = nums[i];
            while (num) {
                int digit = num % 10;
                maxi = max(maxi, digit);
                mini = min(mini, digit);
                num /= 10;
            }
            if (maxi - mini == max_range) {
                sum += nums[i];
            } else if (maxi - mini > max_range) {
                max_range = maxi - mini;
                sum = nums[i];
            }
        }
        return sum;
    }
};