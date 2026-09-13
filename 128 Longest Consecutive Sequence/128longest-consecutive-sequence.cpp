class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }
        sort(nums.begin(), nums.end());
        int maxi = 0;
        int j = 0, i = 1;
        for (i = 1; i < nums.size(); ++i) {
            int gap = abs(nums[i] - nums[i-1]);
            if (gap > 1) {
                maxi = max(maxi, i - j);
                j = i;
            } else {
                if (!gap) {
                    j++;
                }
            }
        }
        maxi = max(maxi, i - j);
        return maxi;
    }
};