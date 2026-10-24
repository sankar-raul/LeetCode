class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {

        int maxi = -1e9, mini = 1e9;
        long long count = 0;
        int j = 0;

        for (int i = 0; i < nums.size(); ++i) {
            maxi = max(maxi, nums[i]);
            mini = min(mini, nums[i]);

            if (mini >= minK && maxi <= maxK) {
                count += i - j + 1;
            } else {
                mini = 1e9;
                maxi = -1e9;
                j = i + 1;
            }
        }

        return count;
    }
};