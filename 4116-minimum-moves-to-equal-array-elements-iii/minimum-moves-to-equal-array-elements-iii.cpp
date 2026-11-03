class Solution {
public:
    int minMoves(vector<int>& nums) {
        int sum = 0, maxi = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            maxi = max(maxi, nums[i]);
        }
        return maxi * n - sum;
    }
};