class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i) {
            nums[i] += nums[i-1];
        }
        for (int i = 0; i < nums.size(); ++i) {
            int left = i == 0 ? 0 : nums[i-1];
            int right = i == nums.size()-1 ? 0 : nums[nums.size() - 1] - nums[i];
            if (left == right) return i;
        }
        return -1;
    }
};