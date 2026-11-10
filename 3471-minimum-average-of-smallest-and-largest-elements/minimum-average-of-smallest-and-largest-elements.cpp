class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size() - 1;
        double min_avg = 51;
        while (i < j) {
            min_avg = fmin(min_avg, (nums[i++] + nums[j--]) / 2.0);
        }
        return min_avg;
    }
};