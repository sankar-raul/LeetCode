class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        if (nums.size() == k) {
            int max_n = nums[0];
            for (int num : nums) {
                max_n = max(max_n, num);
            }
            return max_n;
        }
        map<int, int, greater<int>> freq;
        for (int num : nums) {
            freq[num]++;
        }
        if (k == 1) {
            for (auto &pair : freq) {
                if (pair.second == 1) {
                    return pair.first;
                }
            }
            return -1;
        }
        if (freq[nums[0]] == 1 && freq[nums[nums.size() - 1]] == 1)
            return nums[0] > nums[nums.size() - 1] ? nums[0] : nums[nums.size() - 1];
        if (freq[nums[nums.size() - 1]] == 1) return nums[nums.size() - 1];
        if (freq[nums[0]] == 1) return nums[0];
        return -1;
    }
};