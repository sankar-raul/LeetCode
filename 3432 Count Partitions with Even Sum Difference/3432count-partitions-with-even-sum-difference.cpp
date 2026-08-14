class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int evens = 0;
        for (int i = 1; i < nums.size(); ++i) {
            nums[i] += nums[i-1];
        }
        for (int i = 0; i < nums.size() - 1; ++i) {
            int left_sum = nums[i];
            int right_sum = nums[nums.size() - 1] - left_sum;
            if ((left_sum - right_sum) % 2 == 0)
                evens++;
        }
        return evens;
    }
};