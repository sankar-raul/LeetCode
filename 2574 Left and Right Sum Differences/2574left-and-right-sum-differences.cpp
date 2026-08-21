class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        vector<int> left(nums.size(), 0);
        vector<int> ans(nums.size());
        for (int i = 1; i < nums.size(); ++i) {
            left[i] = left[i-1] + nums[i-1];
        }
        int right = 0;
        for (int i = nums.size() - 1; i >= 0; --i) {
            int tmp = right;
            right += nums[i];
            nums[i] = tmp;
        }
        for (int i = 0; i < nums.size(); ++i) {
            left[i] = abs(left[i] - nums[i]);
        }
        return left;
    }
};