class Solution {
public:
    int findGap(vector<int>& nums, int num) {
        int i = 0, j = nums.size() - 1;
        while (nums[i] != num || nums[j] != num) {
            if (nums[i] != num) i++;
            if (nums[j] != num) j--;
        }
        return j - i + 1;
    }
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> freq;
        int max_freq = 0;
        for (int num : nums) {
            int fr = ++freq[num];
            if (fr >= max_freq) {
                max_freq = fr;
            }
        }
        vector<int> tops;
        for (auto &pair : freq) {
            if (pair.second == max_freq)
                tops.push_back(pair.first);
        }
        int count = INT_MAX;
        for (int num : tops) {
            count = min(count, findGap(nums, num));
        }
        return count;
    }
};