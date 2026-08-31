class Solution {
public:
    vector<int> rotateElements(vector<int>& nums, int k) {
        vector<int> positives;
        for (int num : nums) {
            if (num >= 0) {
                positives.push_back(num);
            }
        }
        if (positives.size() <= 1) return nums; 
        k %= positives.size();
        if (k==0) return nums;
        reverse(positives.begin(), positives.begin() + k);
        reverse(positives.begin() + k, positives.end());
        reverse(positives.begin(), positives.end());
        int j = 0;
        for (int i = 0; i < nums.size(); ++i) {
            nums[i] = nums[i] < 0 ? nums[i] : positives[j++];
        }
        return nums;
    }
};